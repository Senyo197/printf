#include "main.h"

/**
  * print_char - print a character
  *@types: list of arguments
  *@buffer: array of arguments
  *@flags: calculates flags
  *@size: calculates size
  *@width: calculates width
  *@precision: specifiers precision
  *Return: number of printed characters
  */
int print_char(va_list types, char buffer[], int flags, int width, int size,
		int precision)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, precision, size, width, flags));
}

/**
  *print_string - print strings
  *@buffer: array of characters
  *@types: list of characters
  *@precision: specifiers precision
  *@width: gets width
  *@size: gets size
  *@flags: gets flags
  *Return: printed characters
  */
int print_string(va_list types, char buffer[], int width, int size, int flags,
		int precision)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(size);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(flags);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width < length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/**
  *print_percent - print percent symbol
  *@types: list of characters
  *@size: gets size
  *@buffer: array of characters
  *@width: gets width
  *@precision: gets precision
  *@flags: gets flags
*Return: printed characters
*/
int print_percent(va_list types, char buffer[], int size, int flags,
		int precision, int width)
{
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(flags);
	UNUSED(types);
	return (write(1, "%%", 1));
}

/**
  *print_int - prints integer
  *@buffer: array of characters
  *@size: gets size
  *@types: list of characters
  *@width: gets width
  *@flags: gets flags
  *@precision: specifies precision
  *Return: printed characters
  */
int print_int(va_list types, char buffer[], int size, int flags, int width, int precision)
{
	int i = BUF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, size,
				precision));
}

/**
  *print_binary - print binary
  *@types: list of characters
  *@buffer: array of characters
  *@flags: gets flags
  *@width: gets width
  *@size: gets size
  *@precision: specifies precision
  *Return: printed character
  */
int print_binary(va_list types, char buffer[], int flags, int size, int width,
		int precision)
{
	unsigned int n, i, sum, m;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(size);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(flags);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;

	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = a[i] + '0';

			write(1, &z, 1);
			count++;
		}

	}
	return (count);
}
