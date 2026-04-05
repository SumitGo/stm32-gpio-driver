#include <stdint.h>

/* Symbols from linker script */
extern uint32_t _estack;
extern uint32_t _sidata;  // start of init values in flash
extern uint32_t _sdata;   // start of .data in RAM
extern uint32_t _edata;   // end of .data
extern uint32_t _sbss;    // start of .bss
extern uint32_t _ebss;    // end of .bss

int main(void);

/* Function prototypes */
void Reset_Handler(void);
void Default_Handler(void);

/* Weak aliases for interrupt handlers */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));

/* Vector table */
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void)) &_estack,  // Initial stack pointer
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
};

/* Reset Handler */
void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    /* Copy .data from flash to RAM */
    while (dst < &_edata)
    {
        *dst++ = *src++;
    }

    /* Zero initialize .bss */
    dst = &_sbss;
    while (dst < &_ebss)
    {
        *dst++ = 0;
    }

    /* Call main */
    main();

    /* If main returns, loop forever */
    while (1);
}

/* Default interrupt handler */
void Default_Handler(void)
{
    while (1);
}