# STM32 Bare Metal LED Blinking (NO HAL)
This project demonstrates bare metal c programming on a STM32F100RB microcontroller board(STM32VLDiscovery).
No HAL or CMSIS abstraction.

## Workings:
1. The system boots from `startup.c`, which initialises the stack pointer and vector table.
2. Control is  passed to `main()`.
3. GPIO peripheral Clock is enabled using RCC.
4. Pin 9 is configured as Output.
5. LED is toggles via direct register in a direct loop.

## How to Run this Project
This project uses QEMU board emulation and GDB for debugging.

### Requirements
- arm-none-eabi-gcc
- qemu-system-arm
- gdb

### Build firmware
- Run the following command to get the firmware.elf file with debug options
`arm-none-eabi-gcc -mcpu=cortex-m3 -g -nostdlib -T linker.ld startup.c main.c -o firmware.elf`

### Run in qemu
Load the firmware.elf file in qemu for emulation, and also open a port for debugging
`qemu-system-arm -M stm32vldiscovery -nographic -kernel firmware.elf -S -gdb tcp::1234`

### Debugging
- open another terminal and type the following command
  ` gdb-multiarch firmware.elf`
  the gdb terminal starts.
  Type:
  (gdb) `target remote :1234`
Now we can debug in this terminal.


## Learnings:

1. ARM Cortex-M bootup process
2. Writing startup script and Linker Scripts
3. Memory layout understanding
4. Debugging with gdb

## Important Documents
1. User Guide of the board
2. Datasheet of the Microcontroller(STM32F100RB used here)
3. Reference manual of Microcontroller.
