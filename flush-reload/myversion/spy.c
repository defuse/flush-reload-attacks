#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "args.h"
#include "exitcodes.h"
#include "flushreload.h"

static struct option long_options[] = {
    { "help",               no_argument,        NULL, 'h' },
    { "elf",                required_argument,  NULL, 'e' },
    { "threshold",          required_argument,  NULL, 't' },
    { "slot",               required_argument,  NULL, 's' },
    { "probe",              required_argument,  NULL, 'p' },
    { "machine-readable",   no_argument,        NULL, 'm' },
    { NULL, 0, NULL, 0 }
};

const char *program_name;

void showHelp(const char *msg);
void parseArgs(int argc, char **argv, args_t *args);
void validateArgs(const args_t *args);

int main(int argc, char **argv)
{
    program_name = argv[0];

    args_t args;
    args.probes = malloc(MAX_PROBES * sizeof(probe_t));
    if (args.probes == NULL) {
        perror("Couldn't map probes memory.");
        return EXIT_FAILURE;
    }
    args.probe_count = 0;
    args.elf_path = NULL;
    args.threshold = 120; /* Default, will work for most systems. */
    args.slot = 0;
    args.machine_readable = 0;

    parseArgs(argc, argv, &args);
    validateArgs(&args);
    startSpying(&args);

    return EXIT_SUCCESS;
}

void showHelp(const char *msg)
{
    if (msg != NULL) {
        printf("[!] %s\n", msg);
    }
    printf("Usage: %s -e ELFPATH -t CYCLES -s CYCLES -p PROBE [-p PROBE ...] [-m]\n", program_name);
    puts("    -e, --elf PATH\t\t\tPath to ELF binary to spy on.");
    puts("    -t, --threshold CYCLES\t\tMax. L3 latency.");
    puts("    -s, --slot CYCLES\t\t\tSlot duration in cycles.");
    puts("    -p, --probe N:0xDEADBEEF\t\tName character : Virtual address.");
    puts("    -m, --machine-readable\t\tBinary output.");
}

void parseArgs(int argc, char **argv, args_t *args)
{
    int optChar = 0;
    const char *argstr;
    args->probe_count = 0;
    while ( (optChar = getopt_long(argc, argv, "he:t:s:p:m", long_options, NULL)) != -1 ) {
        switch (optChar) {
            case 'h':
                /* Help menu. */
                showHelp(NULL);
                exit(EXIT_SUCCESS);
            case 'e':
                /* ELF path. */
                args->elf_path = optarg;
                break;
            case 'p':
                /* Probe like A:0x400403 */
                argstr = optarg;

                if (args->probe_count >= MAX_PROBES) {
                    showHelp("You've exceeded the maximum amount of probes.");
                    exit(EXIT_BAD_ARGUMENTS);
                }

                probe_t *probe = &args->probes[args->probe_count];

                /* Grab the name character from the front. */
                if (strlen(argstr) >= 2 && isprint(argstr[0]) && argstr[1] == ':') {
                    probe->name = argstr[0];
                } else {
                    showHelp("Give the probe a 1-character name like A:0xDEADBEEF.");
                    exit(EXIT_BAD_ARGUMENTS);
                }

                /* Skip over the colon. */
                argstr += 2;

                if (strlen(argstr) < 2 || argstr[0] != '0' || argstr[1] != 'x') {
                    showHelp("Probe address must be given in hex (starting with 0x)");
                    exit(EXIT_BAD_ARGUMENTS);
                }

                /* Parse the remainder as an integer in hex. */
                if (sscanf(argstr, "%10li", &probe->virtual_address) != 1 || probe->virtual_address <= 0) {
                    showHelp("Bad probe address.");
                    exit(EXIT_BAD_ARGUMENTS);
                }

                args->probe_count++;

                break;
            case 't':
                /* Threshold */
                if (sscanf(optarg, "%10u", &args->threshold) != 1 || args->threshold <= 0) {
                    showHelp("Bad threshold (must be an integer > 0).");
                    exit(EXIT_BAD_ARGUMENTS);
                }
                break;
            case 's':
                /* Slot */
                if (sscanf(optarg, "%10u", &args->slot) != 1 || args->slot <= 0) {
                    showHelp("Bad slot (must be an integer > 0).");
                    exit(EXIT_BAD_ARGUMENTS);
                }
                break;
            case 'm':
                args->machine_readable = 1;
                break;
            default:
                showHelp("Invalid argument.");
                exit(EXIT_BAD_ARGUMENTS);
        }
    }
}

void validateArgs(const args_t *args)
{
    if (args->elf_path == NULL) {
        showHelp("Tell me what program to spy on with --elf.");
        exit(EXIT_BAD_ARGUMENTS);
    }

    if (args->probe_count <= 0) {
        showHelp("Tell me which addresses you want me to probe with --probe.");
        exit(EXIT_BAD_ARGUMENTS);
    }

    if ( ! (0 < args->threshold && args->threshold < 2000) ) {
        showHelp("Bad threshold cycles value. Try 120?");
        exit(EXIT_BAD_ARGUMENTS);
    }

    if (args->slot <= 0) {
        showHelp("Bad slot cycles value. Try 2048?");
        exit(EXIT_BAD_ARGUMENTS);
    }

    /* Check for duplicated probe names or addresses. */
    int i = 0;
    int j = 0;
    for (i = 0; i < args->probe_count; i++) {
        for (j = i + 1; j < args->probe_count; j++) {
            if (args->probes[i].name == args->probes[j].name) {
                showHelp("Two probes share the same name. This is not allowed.");
                exit(EXIT_BAD_ARGUMENTS);
            }

            if (args->probes[i].virtual_address == args->probes[j].virtual_address) {
                showHelp("Two probes share the same virtual address. This is not allowed.");
                exit(EXIT_BAD_ARGUMENTS);
            }
        }
    }
}
