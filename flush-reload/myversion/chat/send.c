#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void hitProbe(const char *ls, int offset)
{
    int x = ls[offset];
    if (x == 0) {
        /* so it doesn't get optimized out XXX */
        printf(".\n");
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./send <bits>\n");
        return 1;
    }

    int fd;
    struct stat sb;
    const char *ls;
    int i, j, k;

    fd = open("/bin/ls", O_RDONLY);
    if (fd < 0) {
        printf("Opening file failed.\n");
    }
    fstat(fd, &sb);

    ls = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

    if (ls == MAP_FAILED)
    {
        printf("mmap() failed.\n");
        return 1;
    }

    for (;;) {
        for (i = 0; i < strlen(argv[1]); i++) {
            for (k = 0; k < 10; k++) {
                for (j = 0; j < 5; j++) {
                    if (argv[1][i] == '1') {
                        hitProbe(ls, 0);
                        hitProbe(ls, 0x1000);
                    } else if (argv[1][i] == '0') {
                        hitProbe(ls, 0);
                        hitProbe(ls, 0x5000);
                    } else {
                        printf("Not bits!\n");
                        return 1;
                    }
                }
                usleep(1000);
            }
        }
    }
}
