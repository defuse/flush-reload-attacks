#include <stdio.h>

#include <stdint.h>

#include "flushreload.h"

typedef struct CpuIdRegisters {
    uint32_t eax, ebx, ecx, edx;
} cpuid_regs_t;

void cpuid(uint32_t eax, cpuid_regs_t *regs)
{
    asm __volatile__ (
        " movl %4, %%eax \n"
        " cpuid \n"
        " movl %%eax, %0 \n"
        " movl %%ebx, %1 \n"
        " movl %%ecx, %2 \n"
        " movl %%edx, %3 \n"
        : "=rm" (regs->eax), "=rm" (regs->ebx), "=rm" (regs->ecx), "=rm" (regs->edx)
        : "irm" (eax)
        : "%eax", "%ebx", "%ecx", "%edx"
    );
}

int has_invariant_tsc()
{
    cpuid_regs_t regs;
    cpuid(0x80000007, &regs);
    if (regs.edx & 0x10) {
        return 1;
    } else {
        return 0;
    }
}

void print_vendor_info()
{
    cpuid_regs_t regs;
    regs.eax = 0xFFFFFFFF;
    regs.ebx = 0xFFFFFFFF;
    regs.ecx = 0xFFFFFFFF;
    regs.edx = 0xFFFFFFFF;
    cpuid(0x00, &regs);
    uint32_t vendor[4] = {regs.ebx, regs.edx, regs.ecx, 0};
    int i = 0;
    for (i = 0; i < 4; i++) { printf("%x\n", vendor[i]); }
    const char *vendor_str = (char *)vendor;
    printf("Vendor: %s\n", vendor_str);
}

void startSpying(args_t *args)
{
    printf("Spying!\n");

    if (has_invariant_tsc()) {
        printf("Yes!\n");
    }

    /* Find the virtual address the victim binary gets loaded at. */

    /* Map the victim binary into our address space. */

    /* Construct pointers to the probe addresses. */

    /* Start the attack. */
}
