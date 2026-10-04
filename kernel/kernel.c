#include "clock.h"
#include "printk.h"
#include "systick.h"
#include "uart.h"
#include "board.h"

void kernel_main(void)
{
    clock_init();
    systick_init();
    uart_init();

    delay_ms(50);

    printk("\n");
    printk("OS Boot OK\n");
    printk("SYSCLK %u Hz\n", SystemCoreClock);
    printk("AHB %u Hz APB1 %u Hz APB2 %u Hz\n", AHB_FREQ, APB1_FREQ, APB2_FREQ);
    printk("CONSOLE USART1 %u baud\n", CONSOLE_BAUD);

    for (;;) {
    }
}
