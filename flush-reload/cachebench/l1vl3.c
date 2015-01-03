#include <stdio.h>
#include <stdlib.h>

#define SAMPLES 100000
#define CACHE_LINE 64

inline int time_access_no_flush(const char *adrs) {
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
    : "=a" (time)
    : "c" (adrs)
    :  "%esi", "%edx");
  return time;
}

inline void flush(const char *adrs) {
  asm __volatile__ ("mfence\nclflush 0(%0)" : : "r" (adrs) :);
}

const char x[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00"
                 "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\x00"
                 "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\x00"
                 "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\x00";


int main (int argc, char **argv)
{
    unsigned int *times = malloc(SAMPLES * sizeof(unsigned int));
    if (times == NULL) {
        return 1;
    }

    int i;
    for (i = 0; i < SAMPLES; i++) {
        // Flush the first time, and then every second time.
        // So that it's uncached, cached, uncached, cached, ...
        if (i % 2 == 0) {
            flush(x);
        }
        times[i] = time_access_no_flush(x);
    }

    for (i = 0; i < SAMPLES; i++) {
        printf("%u\n", times[i]);
    }
    return 0;
}
