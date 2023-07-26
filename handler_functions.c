#include "main.h"

/**
  *handle_write_char - print strings
  *@c: charracter type
  *@buffer: array of charcaters
  *@size: specifies size
  *@precision: specifies precision
  *@width: gets width
  *@flags: gets flags
  *Return: number of character to be printed
  */
int handle_write_char(char c, char buffer[], int size, int precision,
		int width, int flags)
{
	int a = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = ' ';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUF_SIZE - 1] = '\0';

		for (a = 0; a < width - 1; a++)
			buffer[BUF_SIZE - a - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
  *write_number - prints a string
  *@is_negative: Lista of arguments
  *@ind: character type
  *@buffer: array of charcaters
  *@size: specifies size
  *@precision: specifies precision
  *@width: gets width
  *@flags: calculates flags
  *Return: printed characters
  */
int write_number(int is_negative, int ind, char buffer[], int size,
		int precision, int width, int flags)
{
	int length = BUF_SIZE - ind - 1;

	char padd = ' ';
	char extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_num(ind, buffer, length, extra_char, padd, precision,
				width, flags));
}

/**
  *write_num - Write a number using a bufffer
  *@ind: Index at which the number starts on the buffer
  *@buffer: an array of characters
  *@flags: calculates flags
  *@width: gets width
  *@precision: specifies precision
  *@length: length of character
  *@padd: padding character
  *@extra_char: extra character
  *Return: printed characters
  */
int write_num(int ind, char buffer[], int flags, int width, int precision,
		int length, char padd, char extra_char)
{
	int a, padd_start = 1;

	if (precision == 0 && ind == BUF_SIZE - 2 && buffer[ind] == '0' &&
			width == 0)
		return (0);
	if (precision == 0 && ind == BUF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
		buffer[--ind] = '0', length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padd;
		buffer[a] = '\0';

		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return (write(1, &buffer[padd_start], a - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}

	}
	if (extra_char)
		buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], length));
}

/**
  *write_unsgnd - writes an unsigned number
  *@is_negative: Number indicating if the num is negative
  *@ind: number index
  *@buffer: array of characters
  *@flags: calculates flags
  *@width: gets width
  *@size: gets size
  *@precision: specifies precision
  *Return: printed characters
  */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = BUF_SIZE - ind - 1, a = 0;

	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (a = 0; a < width - length; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
	}
	if (flags & F_MINUS)
	{
		return (write(1, &buffer[ind], length) + write(1, &buffer[0], a));
	}
	else
	{
		return (write(1, &buffer[0], a) + write(1, &buffer[ind], length));
	}
	return (write(1, &buffer[ind], length));
}

/**
  *write_pointer - Write a memory address
  *@buffer: array of characters
  *@ind: Index at which the number starts in the buffer
  *@length: length of character
  *@width: gets width
  *@flags: gets flags
  *@padd: padding character
  *@extra_char: extra character
  *@padd_start: ndex at which padding should start
  *Return: printed character
  */
int write_pointer(char buffer[], int ind, int length, int width, int flags,
		char padd, char extra_char, int padd_start)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3],
						a - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[3], a - 3) +
					write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_char)
		buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], BUF_SIZE - ind - 1));
}
