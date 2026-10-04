#ifndef STM32F407_H
#define STM32F407_H

#include <stdint.h>

#define RCC_BASE        0x40023800UL
#define PWR_BASE        0x40007000UL
#define FLASH_BASE      0x40023C00UL
#define GPIOA_BASE      0x40020000UL
#define GPIOB_BASE      0x40020400UL
#define GPIOC_BASE      0x40020800UL
#define GPIOD_BASE      0x40020C00UL
#define GPIOE_BASE      0x40021000UL
#define GPIOF_BASE      0x40021400UL
#define GPIOG_BASE      0x40021800UL
#define GPIOH_BASE      0x40021C00UL
#define USART1_BASE     0x40011000UL
#define USART2_BASE     0x40004400UL
#define USART3_BASE     0x40004800UL
#define SYSTICK_BASE    0xE000E010UL
#define SCB_BASE        0xE000ED00UL

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t OPTCR;
} FLASH_TypeDef;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CSR;
} PWR_TypeDef;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_TypeDef;

typedef struct {
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint8_t  SHP[12];
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t DFSR;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;
    volatile uint32_t AFSR;
    volatile uint32_t CPACR;
} SCB_TypeDef;

#define RCC         ((RCC_TypeDef *)RCC_BASE)
#define PWR         ((PWR_TypeDef *)PWR_BASE)
#define FLASH       ((FLASH_TypeDef *)FLASH_BASE)
#define GPIOA       ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD       ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE       ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF       ((GPIO_TypeDef *)GPIOF_BASE)
#define GPIOG       ((GPIO_TypeDef *)GPIOG_BASE)
#define GPIOH       ((GPIO_TypeDef *)GPIOH_BASE)
#define USART1      ((USART_TypeDef *)USART1_BASE)
#define USART2      ((USART_TypeDef *)USART2_BASE)
#define USART3      ((USART_TypeDef *)USART3_BASE)
#define SYSTICK     ((SysTick_TypeDef *)SYSTICK_BASE)
#define SCB         ((SCB_TypeDef *)SCB_BASE)

#define RCC_CR_HSEON            (1UL << 16)
#define RCC_CR_HSERDY           (1UL << 17)
#define RCC_CR_HSEBYP           (1UL << 18)
#define RCC_CR_CSSON            (1UL << 19)
#define RCC_CR_PLLON            (1UL << 24)
#define RCC_CR_PLLRDY           (1UL << 25)

#define RCC_PLLCFGR_PLLM_POS    0U
#define RCC_PLLCFGR_PLLM_MASK   (0x3FUL << RCC_PLLCFGR_PLLM_POS)
#define RCC_PLLCFGR_PLLN_POS    6U
#define RCC_PLLCFGR_PLLN_MASK   (0x1FFUL << RCC_PLLCFGR_PLLN_POS)
#define RCC_PLLCFGR_PLLP_POS    16U
#define RCC_PLLCFGR_PLLP_MASK   (0x3UL << RCC_PLLCFGR_PLLP_POS)
#define RCC_PLLCFGR_PLLSRC_HSE  (1UL << 22)
#define RCC_PLLCFGR_PLLSRC_MASK (1UL << 22)
#define RCC_PLLCFGR_PLLQ_POS    24U
#define RCC_PLLCFGR_PLLQ_MASK   (0xFUL << RCC_PLLCFGR_PLLQ_POS)

#define RCC_CFGR_SW_MASK        (0x3UL << 0)
#define RCC_CFGR_SW_PLL         (0x2UL << 0)
#define RCC_CFGR_SWS_MASK       (0x3UL << 2)
#define RCC_CFGR_SWS_PLL        (0x2UL << 2)
#define RCC_CFGR_HPRE_MASK      (0xFUL << 4)
#define RCC_CFGR_HPRE_DIV1      (0x0UL << 4)
#define RCC_CFGR_PPRE1_MASK     (0x7UL << 10)
#define RCC_CFGR_PPRE1_DIV4     (0x5UL << 10)
#define RCC_CFGR_PPRE2_MASK     (0x7UL << 13)
#define RCC_CFGR_PPRE2_DIV2     (0x4UL << 13)

#define RCC_AHB1ENR_GPIOAEN     (1UL << 0)
#define RCC_AHB1ENR_GPIOBEN     (1UL << 1)
#define RCC_AHB1ENR_GPIOCEN     (1UL << 2)
#define RCC_AHB1ENR_GPIODEN     (1UL << 3)
#define RCC_AHB1ENR_GPIOEEN     (1UL << 4)
#define RCC_AHB1ENR_GPIOFEN     (1UL << 5)
#define RCC_AHB1ENR_GPIOGEN     (1UL << 6)
#define RCC_AHB1ENR_GPIOHEN     (1UL << 7)

#define RCC_APB1ENR_PWREN       (1UL << 28)
#define RCC_APB2ENR_USART1EN    (1UL << 4)
#define RCC_APB2ENR_USART6EN    (1UL << 5)

#define FLASH_ACR_LATENCY_MASK  (0x7UL << 0)
#define FLASH_ACR_LATENCY_5WS   (0x5UL << 0)
#define FLASH_ACR_PRFTEN        (1UL << 8)
#define FLASH_ACR_ICEN          (1UL << 9)
#define FLASH_ACR_DCEN          (1UL << 10)

#define PWR_CR_VOS              (1UL << 14)

#define USART_SR_RXNE           (1UL << 5)
#define USART_SR_TC             (1UL << 6)
#define USART_SR_TXE            (1UL << 7)
#define USART_CR1_RE            (1UL << 2)
#define USART_CR1_TE            (1UL << 3)
#define USART_CR1_UE            (1UL << 13)

#define SYSTICK_CTRL_ENABLE     (1UL << 0)
#define SYSTICK_CTRL_TICKINT    (1UL << 1)
#define SYSTICK_CTRL_CLKSOURCE  (1UL << 2)
#define SYSTICK_CTRL_COUNTFLAG  (1UL << 16)
#define SYSTICK_LOAD_RELOAD_MASK (0xFFFFFFUL)

#define GPIO_MODE_INPUT         0x0UL
#define GPIO_MODE_OUTPUT        0x1UL
#define GPIO_MODE_AF            0x2UL
#define GPIO_MODE_ANALOG        0x3UL
#define GPIO_MODE_MASK          0x3UL

#define GPIO_PUPD_NONE          0x0UL
#define GPIO_PUPD_PULLUP        0x1UL
#define GPIO_PUPD_PULLDOWN      0x2UL
#define GPIO_PUPD_MASK          0x3UL

#define GPIO_OSPEED_LOW         0x0UL
#define GPIO_OSPEED_MEDIUM      0x1UL
#define GPIO_OSPEED_HIGH        0x2UL
#define GPIO_OSPEED_VERY_HIGH   0x3UL
#define GPIO_OSPEED_MASK        0x3UL

#define GPIO_AF_MASK            0xFUL

#endif
