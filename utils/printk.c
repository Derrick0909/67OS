#include <stdint.h>
#include "printk.h"
#include "uart.h"

static void print_number(uint32_t value, uint32_t base, uint32_t upper)
{
    static const char lower_digits[] = "0123456789abcdef";
    static const char upper_digits[] = "0123456789ABCDEF";
    const char *digits = (upper != 0UL) ? upper_digits : lower_digits;
    char buffer[32];
    uint32_t index = 0UL;

    if (value == 0UL) {
        usart_putc('0');
        return;
    }

    while (value != 0UL) {
        buffer[index++] = digits[value % base];
        value /= base;
    }

    while (index != 0UL) {
        usart_putc(buffer[--index]);
    }
}

static void print_signed(int32_t value)
{
    if (value < 0) {
        usart_putc('-');
        print_number((uint32_t)(-(value + 1)) + 1UL, 10UL, 0UL);
    } else {
        print_number((uint32_t)value, 10UL, 0UL);
    }
}

void vprintk(const char *fmt, va_list args)
{
    while (*fmt != '\0') {
        if (*fmt != '%') {
            usart_putc(*fmt++);
            continue;
        }

        fmt++;

        switch (*fmt) {
        case 'c':
            usart_putc((char)va_arg(args, int));
            break;
        case 's': {
            const char *text = va_arg(args, const char *);
            usart_puts((text != 0) ? text : "(null)");
            break;
        }
        case 'd':
        case 'i':
            print_signed(va_arg(args, int));
            break;
        case 'u':
            print_number(va_arg(args, unsigned int), 10UL, 0UL);
            break;
        case 'x':
            print_number(va_arg(args, unsigned int), 16UL, 0UL);
            break;
        case 'X':
            print_number(va_arg(args, unsigned int), 16UL, 1UL);
            break;
        case 'p':
            usart_puts("0x");
            print_number((uint32_t)(uintptr_t)va_arg(args, void *), 16UL, 0UL);
            break;
        case '%':
            usart_putc('%');
            break;
        case '\0':
            usart_putc('%');
            return;
        default:
            usart_putc('%');
            usart_putc(*fmt);
            break;
        }

        fmt++;
    }
}

void printk(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprintk(fmt, args);
    va_end(args);
}
