#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void hitProbe(int fd, int offset)
{
    char buf[16];
    lseek(fd, offset, SEEK_SET);
    read(fd, buf, 16);
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

    fd = open("/usr/bin/ls", O_RDONLY);
    if (fd < 0) {
        printf("Opening file failed.\n");
    }

    for (;;) {
        for (i = 0; i < strlen(argv[1]); i++) {
            for (k = 0; k < 10; k++) {
                for (j = 0; j < 5; j++) {
                    if (argv[1][i] == '1') {
                        hitProbe(fd, 0);
                        hitProbe(fd, 0x1000);
                    } else if (argv[1][i] == '0') {
                        hitProbe(fd, 0);
                        hitProbe(fd, 0x5000);
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
