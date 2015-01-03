#ifndef ARGS_H
#define ARGS_H

typedef struct Probe {
    unsigned long virtual_address;
    const char *mapped_pointer;
    char name;
} probe_t;

typedef struct SpyArguments {
    const char *elf_path;
    unsigned int threshold;
    unsigned int slot;
    probe_t *probes;
    unsigned int probe_count;
    unsigned int machine_readable;
} args_t;

#endif
