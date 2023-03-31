#include "main.h"
/**
 * handler - Prints an argument based on its type
 * @fprint: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handler(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fprint fprint_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fprint_types[i].fprint != '\0'; i++)
		if (fprint[*ind] == fprint_types[i].fprint)
			return (fprint_types[i].fn(list, buffer, flags, width, precision, size));

	if (fprint_types[i].fprint == '\0')
	{
		if (fprint[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fprint[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fprint[*ind] != ' ' && fprint[*ind] != '%')
				--(*ind);
			if (fprint[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fprint[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
