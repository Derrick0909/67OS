#include "uart.h"
#include "board.h"

static void uart_setup_pin(uint32_t pin)
{
    uint32_t mode_pos = pin * 2UL;
    uint32_t afr_index = pin >> 3;
    uint32_t afr_pos = (pin & 7UL) * 4UL;

    CONSOLE_GPIO->MODER = (CONSOLE_GPIO->MODER & ~(GPIO_MODE_MASK << mode_pos)) | (GPIO_MODE_AF << mode_pos);
    CONSOLE_GPIO->OTYPER &= ~(1UL << pin);
    CONSOLE_GPIO->OSPEEDR = (CONSOLE_GPIO->OSPEEDR & ~(GPIO_OSPEED_MASK << mode_pos)) | (GPIO_OSPEED_VERY_HIGH << mode_pos);
    CONSOLE_GPIO->PUPDR = (CONSOLE_GPIO->PUPDR & ~(GPIO_PUPD_MASK << mode_pos)) | (GPIO_PUPD_PULLUP << mode_pos);
    CONSOLE_GPIO->AFR[afr_index] = (CONSOLE_GPIO->AFR[afr_index] & ~(GPIO_AF_MASK << afr_pos)) | (CONSOLE_AF << afr_pos);
}

void uart_init(void)
{
    RCC->AHB1ENR |= CONSOLE_GPIO_EN;
    RCC->APB2ENR |= CONSOLE_USART_EN;

    uart_setup_pin(CONSOLE_TX_PIN);
    uart_setup_pin(CONSOLE_RX_PIN);

    CONSOLE_USART->CR1 = 0UL;
    CONSOLE_USART->CR2 = 0UL;
    CONSOLE_USART->CR3 = 0UL;
    CONSOLE_USART->BRR = (APB2_FREQ + (CONSOLE_BAUD / 2UL)) / CONSOLE_BAUD;
    CONSOLE_USART->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void usart_putc(char c)
{
    while ((CONSOLE_USART->SR & USART_SR_TXE) == 0UL) {
    }

    CONSOLE_USART->DR = (uint32_t)(uint8_t)c;
}

void usart_puts(const char *s)
{
    while (*s != '\0') {
        usart_putc(*s++);
    }
}
