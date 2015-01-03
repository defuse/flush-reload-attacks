#ifndef ELFTOOLS_H
#define ELFTOOLS_H

#include <unistd.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

/* TODO: For practical attacks, we don't want the libelf dependency. */

/* Returns 0 on error. */
unsigned long elf_get_load_address(const char *elf_path)
{
    Elf *e;
    Elf_Kind ek;
    GElf_Ehdr ehdr;
    unsigned long load_address;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "Elf library initialization failed.\n");
        return 0;
    }

    int fd = open(elf_path, O_RDONLY, 0);
    if (fd < 0) {
        fprintf(stderr, "Couldn't open the ELF at %s.\n", elf_path);
        return 0;
    }

    e = elf_begin(fd, ELF_C_READ, NULL);
    if (e == NULL) {
        fprintf(stderr, "elf_begin() failed.\n");
        return 0;
    }

    ek = elf_kind(e);

    if (ek != ELF_K_ELF) {
        fprintf(stderr, "Bad ELF file.\n");
        return 0;
    }

    if (gelf_getehdr(e, &ehdr) == NULL) {
        fprintf(stderr, "Couldn't get the ELF header.\n");
        return 0;
    }

/* TODO: This is a hack, and may not be right. Do it more correctly. */
    switch (gelf_getclass(e)) {
        case ELFCLASS32:
            load_address = 0x08048000;
            break;
        case ELFCLASS64:
            load_address = 0x400000;
            break;
        default:
            fprintf(stderr, "Unknown kind of ELF.\n");
            return 0;
    }

    elf_end(e);
    close(fd);

    return load_address;
}

#endif
