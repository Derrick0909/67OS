Week 1, STM32F407
**Goal**: Boot into C code and print boot log via UART.

1. **Startup assembly `startup.s` 
    Implement `Reset_Handler`: set stack pointer, zero‑out `.bss`, copy `.data`, jump to `kernel_main()`. Create minimal vector table.

2. **Linker script `link.ld` 
    Define Flash / SRAM memory regions. Place interrupt‑vector table at the very start of Flash.

3. **Kernel C code
    - Direct register‑level RCC setup: HSE → PLL, configure SYSCLK to 168 MHz.
    - USART1 driver: implement `usart_putc()`, minimal `printk()`.
    - In `kernel_main()`, call `printk()` to output boot message.

4. **Project & test
    Write Makefile: build elf/bin, flash via ST‑Link.
    ✅ Acceptance: Power‑on prints `OS Boot OK` over serial; debug confirms SP and clock settings are correct.

> Optional (do if extra time): Simple SysTick delay function.