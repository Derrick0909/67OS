#ifndef PRINTK_H
#define PRINTK_H

#include <stdarg.h>

void vprintk(const char *fmt, va_list args);
void printk(const char *fmt, ...);

#endif
