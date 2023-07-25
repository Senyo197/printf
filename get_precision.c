#include "main.h"
/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */

int get_precision(const char *format, int *i, va_list list)
{
	int curr_ind = *i + 1;
	int precision = -1;

	if (format[curr_ind] != '.')
		return (precision);

	precision = 0;

	for (curr_ind += 1; format[curr_ind] != '\0'; curr_ind++)
	{
		if (is_digit(format[curr_ind]))
		{
			precision *= 10;
			precision += format[curr_ind] - '0';
		}
		else if (format[curr_ind] == '*')
		{
			curr_ind++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_ind - 1;

	return (precision);
}
