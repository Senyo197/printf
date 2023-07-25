#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: string format
i * @i: takes a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int r, current_index;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_index = *i + 1; format[current_index] != '\0'; current_index++)
	{
		for (r = 0; FLAGS_CH[r] != '\0'; r++)
			if (format[current_index] == FLAGS_CH[r])
			{
				flags |= FLAGS_ARR[r];
				break;
			}

		if (FLAGS_CH[r] == 0)
			break;
	}

	*i = current_index - 1;

	return (flags);
}
