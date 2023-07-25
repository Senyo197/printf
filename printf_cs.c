#include "main.h"

/**
  *prnt_buf - print buffer content
  *@buff: array of characters
  *@buff_indx: buffer index
  */
void prnt_buf(char buff[], int *buff_indx)
{
	if (*buff_indx > 0)
	{
		write(1, &buff[0], *buff_indx);

		*buff_indx = 0;
	}
}

/**
  *_printf - prints format specificier of c, s and %
  *@format: a character string
 *Return: 0
 */
int _printf(const char *format, ...)
{
	int z, p1 = 0, p2 = 0;
	int width, size, precision, flags, buff_indx = 0;
	va_list agmts;
	char buff[BUF_SIZE];

	if (format == NULL)
	{
		return (-1);
	}

	va_start(agmts, format);
	for (z = 0; format && format[z] != '\0'; z++)
	{
		if (format[z] == '%')
		{
			buff[buff_indx++] = format[z];

			if (buff_indx == BUF_SIZE)
			{
				prnt_buf(buff, &buff_indx);
			}
			p2++;
		}
		else
		{
			prnt_buf(buff, &buff_indx);
			flags = get_flags(format, &z);
			width = get_width(format, &z, agmts);
			size = get_size(format, &z);
			precision = get_precision(format, &z, agmts);
			z++;
			p1 = handle_print(format, &z, agmts, buff, size, flags, width,
					precision);
			if (p1 == -1)
				return (-1);
			p2 += p1;
		}
	}
	va_end(agmts);
	return (p2);
}
