#include <stdio.h>

#include "flushreload.h"
#include "cpuid.h"

void checkSystemConfiguration()
{
    if (!cpuid_has_invariant_tsc()) {
        printf("WARNING: This processor does not have an invariant TSC.\n");
    }

    /* TODO: warn on multiple procs */
}

void startSpying(args_t *args)
{
    /* Find the virtual address the victim binary gets loaded at. */

    /* Map the victim binary into our address space. */

    /* Construct pointers to the probe addresses. */

    /* Start the attack. */
}
