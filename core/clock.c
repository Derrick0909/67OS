#include "clock.h"
#include "board.h"

uint32_t SystemCoreClock = HSE_VALUE;

static void clock_enable_hse(void)
{
    RCC->CR |= RCC_CR_HSEON;

    while ((RCC->CR & RCC_CR_HSERDY) == 0UL) {
    }
}

static void clock_setup_power(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
}

static void clock_setup_flash(void)
{
    uint32_t acr = FLASH->ACR & ~FLASH_ACR_LATENCY_MASK;

    FLASH->ACR = acr | FLASH_ACR_LATENCY_5WS | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;
}

static void clock_setup_prescalers(void)
{
    uint32_t cfgr = RCC->CFGR;

    cfgr &= ~(RCC_CFGR_HPRE_MASK | RCC_CFGR_PPRE1_MASK | RCC_CFGR_PPRE2_MASK);
    cfgr |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;

    RCC->CFGR = cfgr;
}

static void clock_setup_pll(void)
{
    uint32_t pllcfgr = 0UL;

    pllcfgr |= (PLL_M << RCC_PLLCFGR_PLLM_POS) & RCC_PLLCFGR_PLLM_MASK;
    pllcfgr |= (PLL_N << RCC_PLLCFGR_PLLN_POS) & RCC_PLLCFGR_PLLN_MASK;
    pllcfgr |= (((PLL_P / 2UL) - 1UL) << RCC_PLLCFGR_PLLP_POS) & RCC_PLLCFGR_PLLP_MASK;
    pllcfgr |= (PLL_Q << RCC_PLLCFGR_PLLQ_POS) & RCC_PLLCFGR_PLLQ_MASK;
    pllcfgr |= RCC_PLLCFGR_PLLSRC_HSE;

    RCC->CR &= ~RCC_CR_PLLON;
    RCC->PLLCFGR = pllcfgr;

    RCC->CR |= RCC_CR_PLLON;

    while ((RCC->CR & RCC_CR_PLLRDY) == 0UL) {
    }
}

static void clock_select_pll(void)
{
    uint32_t cfgr = RCC->CFGR & ~RCC_CFGR_SW_MASK;

    RCC->CFGR = cfgr | RCC_CFGR_SW_PLL;

    while ((RCC->CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL) {
    }

    SystemCoreClock = PLLCLK_FREQ;
}

void clock_init(void)
{
    clock_enable_hse();
    clock_setup_power();
    clock_setup_flash();
    clock_setup_prescalers();
    clock_setup_pll();
    clock_select_pll();
}
