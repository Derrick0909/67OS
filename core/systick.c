#include "systick.h"
#include "board.h"

static void systick_wait(void)
{
    while ((SYSTICK->CTRL & SYSTICK_CTRL_COUNTFLAG) == 0UL) {
    }
}

static void systick_ensure_running(void)
{
    SYSTICK->CTRL |= SYSTICK_CTRL_CLKSOURCE | SYSTICK_CTRL_ENABLE;
}

void systick_init(void)
{
    SYSTICK->CTRL = 0UL;
    SYSTICK->LOAD = (SYSTICK_FREQ / 1000UL) - 1UL;
    SYSTICK->VAL = 0UL;
    SYSTICK->CTRL = SYSTICK_CTRL_CLKSOURCE | SYSTICK_CTRL_ENABLE;
}

void delay_us(uint32_t us)
{
    uint32_t ticks = us * (SYSTICK_FREQ / 1000000UL);
    uint32_t reload = SYSTICK->LOAD;

    systick_ensure_running();

    while (ticks != 0UL) {
        uint32_t chunk = (ticks > SYSTICK_LOAD_RELOAD_MASK) ? SYSTICK_LOAD_RELOAD_MASK : ticks;

        SYSTICK->LOAD = chunk - 1UL;
        SYSTICK->VAL = 0UL;
        systick_wait();
        ticks -= chunk;
    }

    SYSTICK->LOAD = reload;
}

void delay_ms(uint32_t ms)
{
    systick_ensure_running();
    SYSTICK->LOAD = (SYSTICK_FREQ / 1000UL) - 1UL;
    SYSTICK->VAL = 0UL;

    while (ms != 0UL) {
        systick_wait();
        ms--;
    }
}
