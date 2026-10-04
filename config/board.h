#ifndef BOARD_H
#define BOARD_H

#include "stm32f407.h"

#define HSE_VALUE           8000000UL
#define LSI_VALUE           32000UL

#define SYSCLK_FREQ         168000000UL

#define PLL_M               8UL
#define PLL_N               336UL
#define PLL_P               2UL
#define PLL_Q               7UL

#define VCO_INPUT_FREQ      (HSE_VALUE / PLL_M)
#define VCO_OUTPUT_FREQ     (VCO_INPUT_FREQ * PLL_N)
#define PLLCLK_FREQ         (VCO_OUTPUT_FREQ / PLL_P)
#define PLL48CLK_FREQ       (VCO_OUTPUT_FREQ / PLL_Q)

#define AHB_FREQ            SYSCLK_FREQ
#define APB1_FREQ           (SYSCLK_FREQ / 4UL)
#define APB2_FREQ           (SYSCLK_FREQ / 2UL)

#define CONSOLE_USART       USART1
#define CONSOLE_USART_EN    RCC_APB2ENR_USART1EN
#define CONSOLE_GPIO        GPIOA
#define CONSOLE_GPIO_EN     RCC_AHB1ENR_GPIOAEN
#define CONSOLE_TX_PIN      9UL
#define CONSOLE_RX_PIN      10UL
#define CONSOLE_AF          7UL
#define CONSOLE_BAUD        115200UL

#define SYSTICK_FREQ        AHB_FREQ

#endif
