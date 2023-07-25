#include "main.h"

/**
  *print_unsigned - print unsigned characters
  *@buffer: array fo characters
  *@types: list of characters
  *@size: gets size
  *@precision: specifies precision
  *@width: gets width
  *@flags: gets flags
  *Return: printed characters
  */
int print_unsigned(va_list types, char buffer[], int size, int precision,
		int width, int flags)
{
	int a = BUF_SIZE - 2;

	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';
	buffer[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}
	a++;
	return (write_unsgnd(0, i, buffer, size, width, flags, precision));
}

/**
  *print_octal - print octal characters
  *@buffer: array of characters
  *@types: list of characters
  *@size: calculates size
  *@width: gets the width
  *@flags: get the flags
  *@precision: specifies precision
  *Return: printed characters
  */
int print_octal(va_list types, char buffer[], int size, int flags, int width,
		int precision)
{
	int a = BUF_SIZE - 2;

	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';
	buffer[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';
	a++;

	return (write_unsgnd(0, i, buffer, size, width, flags, precision));
}

/**
  *print_hexadecimal - prints hexadecimal characters
  *@buffer: array of characters
  *@types: list of characters
  *@flags: get the flags
  *@size: calculates the size
  *@width: gets the width
  *@precision: specifies precision
  *Return: printed characters
  */
int print_hexadecimal(va_list types, int size, char buffer[], int width,
		int precision, int flags)
{
	return (print_hexa(types, "0123456789abcdef", buffer, flags, width, size,
				'x', precision));
}

/**
  *print_hexa_upper - prints hexa_upper characters
  *@types: list of characters
  *@buffer: array of characters
  *@size:calculates size
  *@width: gets the width
  *@flags: get the flags
  *@precision: specifies precision
  *Return: printed characters
  */
int print_hexa_upper(va_list types, char buffer[], int size, int width,
		int flags, int precision)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer, size, flags, width,
				'X', precision));
}

/**
  *print_hexa - prints hexadecimal number in lower or upper
  *@types: list of numbers
  *@buffer: array of numbers
  *@flags: get the flags
  *@width: gets the width
  *@size: calculates the size
  *@precision: specifies precision
  *@map_to: array of values to map the numbers to
  *@flag_ch: calcualtes active flags
  *Return: number of character pairs
  */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';
	buffer[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}
	a++;

	return (write_unsgnd(0, i, buffer, flags, width, size, precision));
}
