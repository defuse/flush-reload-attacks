#ifndef ELFTOOLS_H
#define ELFTOOLS_H

#include <unistd.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

/* TODO: For practical attacks, we don't want to assume the libelf dependency is
 * installed on the victim's system. */

/* Returns ULONG_MAX on error, 0 when the ELF is a shared library.*/
unsigned long elf_get_load_address(const char *elf_path)
{
    Elf *e;
    Elf_Kind ek;
    GElf_Ehdr ehdr;
    unsigned long load_address;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "Elf library initialization failed.\n");
        return ULONG_MAX;
    }

    int fd = open(elf_path, O_RDONLY, 0);
    if (fd < 0) {
        fprintf(stderr, "Couldn't open the ELF at %s.\n", elf_path);
        return ULONG_MAX;
    }

    e = elf_begin(fd, ELF_C_READ, NULL);
    if (e == NULL) {
        fprintf(stderr, "elf_begin() failed.\n");
        return ULONG_MAX;
    }

    ek = elf_kind(e);

    if (ek != ELF_K_ELF) {
        fprintf(stderr, "Bad ELF file.\n");
        return ULONG_MAX;
    }

    if (gelf_getehdr(e, &ehdr) == NULL) {
        fprintf(stderr, "Couldn't get the ELF header.\n");
        return ULONG_MAX;
    }

    if (ehdr.e_type == ET_EXEC) {
        printf("Detected ELF type: Executable.\n");
        /* It's a binary, so return the address it gets loaded at. */
        /* TODO: This is a hack, and may not be right. Do it more correctly. */
        switch (gelf_getclass(e)) {
            case ELFCLASS32:
                load_address = 0x08048000;
                break;
            case ELFCLASS64:
                load_address = 0x400000;
                break;
            default:
                fprintf(stderr, "Unknown ELF class.\n");
                return ULONG_MAX;
        }
    } else if (ehdr.e_type == ET_DYN) {
        printf("Detected ELF type: Shared Object.\n");
        /* It's a shared library, so return zero. */
        /* Objdump addresses are relative to the start of the file. */
        return 0;
    } else {
        fprintf(stderr, "Unknown ELF type.\n");
        return ULONG_MAX;
    }

    elf_end(e);
    close(fd);

    return load_address;
}

#endif
