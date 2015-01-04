#ifndef ATTACKTOOLS_H
#define ATTACKTOOLS_H

void *map(const char *elf_path, unsigned long *size)
{
    int fd = open(elf_path, O_RDONLY);
    if (fd < 0 ) {
        perror("Error opening ELF file.");
        exit(EXIT_FAILURE);
    }

    struct stat st_buf;
    fstat(fd, &st_buf);
    *size = st_buf.st_size;

    void *rv = mmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
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

#endif
