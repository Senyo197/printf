#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define BUF_SIZE 1024

int _putchar(char c);

int _printf(const char *format, ...);
void prnt_buf(char buff[], int *buff_indx);

#endif /* MAIN_H */
