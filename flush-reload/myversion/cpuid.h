#ifndef CPUID_H
#define CPUID_H

#include <stdint.h>

typedef struct CpuIdRegisters {
    volatile uint32_t eax, ebx, ecx, edx;
} cpuid_regs_t;

void cpuid(volatile uint32_t eax, cpuid_regs_t *regs)
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

/*
 * 17.13.1 Invariant TSC (Intel Software Developer's Manual Volume 3B)
 *
 * The time stamp counter in newer processors may support an enhancement,
 * reffered to as invariant TSC. Processor's support for invariant TSC is
 * indicated by CPUID.80000007H:EDX[8].
 *
 * The invariant TSC will run at a constant rate in all ACPI P-, C-. and
 * T-states. This is the architectural behavior moving forward. On processors
 * with invariant TSC support, the OS may use the TSC for wall clock timer
 * services (instead of ACPI or HPET timers). TSC reads are much more efficient
 * and do not incur the overhead associated with a ring transition or access to
 * a platform resource.
 */
int cpuid_has_invariant_tsc()
{
    cpuid_regs_t regs;
    cpuid(0x80000007, &regs);
    if (regs.edx & 0x10) {
        return 1;
    } else {
        return 0;
    }
}

void cpuid_get_vendor_string(char vendor[12])
{
    uint32_t *vendor_as_ints = (uint32_t *)vendor;
    cpuid_regs_t regs;
    cpuid(0x00, &regs);
    vendor_as_ints[0] = regs.ebx;
    vendor_as_ints[1] = regs.edx;
    vendor_as_ints[2] = regs.ecx;
}


#endif
