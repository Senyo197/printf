#include "main.h"

/**
  *_printf - prints format specificier of c, s and %
  *@format: a character string
 *Return: 0
 */
int _printf(const char *format, ...)
{
	int z;
	char c, *s;
	char appr;
	va_list agmts;

	va_start(agmts, format);
	for (z = 0; format[z] != '\0'; z++)
	{
		if (format[z] == '%')
		{
			appr = format[z + 1];
			switch (appr)
			{
				case 'c':
					c = va_arg(agmts, int);
					_putchar(c);
					break;
				case 's':
					s = va_arg(agmts, char *);
					printf("%s", s);
					break;
				case '%':
					_putchar('%');
					_putchar(appr);
					break;
				default:
					_putchar('%');
					_putchar(format[z]);
					break;
			}
			z++;
		}
		else
		{
			_putchar(format[z]);
		}
	}
	va_end(agmts);
	_putchar('\n');
	return (0);
}
