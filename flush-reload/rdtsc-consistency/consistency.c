#include <stdio.h>

inline unsigned long gettime() {
  volatile unsigned long tl;
  asm __volatile__("lfence\nrdtsc" : "=a" (tl): : "%edx");
  return tl;
}

int main(int argc, char **argv)
{
    unsigned long t = gettime();
    unsigned long t2;
    while (1) {
        t2 = gettime();
        if (t2 < t) {
            printf("Monotonicity FAILED! %lu < %lu\n", t2, t);
        }
        t = t2;
    }
}
