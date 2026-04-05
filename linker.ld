ENTRY(Reset_Handler)

/* Memory regions */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

/* Top of stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Vector table goes first in flash */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* Program code and read-only data */
    .text :
    {
        *(.text*)      /* code */
        *(.rodata*)    /* constants */
        _etext = .;
    } > FLASH

    /* Initialized data (goes to RAM, but stored in FLASH) */
    .data : AT(_etext)
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    /* Load address of data (in FLASH) */
    _sidata = LOADADDR(.data);

    /* Uninitialized data */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    /* Optional: heap + stack space marker */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        end = .;
        . = . + 0x400; /* 1KB heap (optional) */
        . = ALIGN(8);
    } > RAM
}