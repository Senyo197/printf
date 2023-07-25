#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int current_ind;
	int width = 0;

	for (current_ind = *i + 1; format[current_ind] != '\0'; current_ind++)
	{
		if (is_digit(format[current_ind]))
		{
			width *= 10;
			width += format[current_ind] - '0';
		}
		else if (format[current_ind] == '*')
		{
			current_ind++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_ind - 1;

	return (width);
}
