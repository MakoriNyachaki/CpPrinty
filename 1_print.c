#include "main.h"

/**
 * _precision - calcutes the turn-around time
 * to print
 *
 * @format: formated string  for printing args
 * @list: args to be printed
 * @vl: list of arguments
 *
 * Return: turn-around time
 */

int _precision(const char *format, int *list, va_list vl)
{
	int list0 = *list + 1, t_time = -1;

	if (format[list0] != '.')
		return (t_time);

	t_time = 0;

	for (list0 += 1; format[list0] != '\0'; list0++)
	{
		if (_digit(format[list0]))
		{
			t_time *= 10;
			t_time += format[list0] - '0';
		}
		else if (format[list0] == '*')
		{
			list0++;
			t_time = va_arg(vl, int);
			break;
		}
		else
		{
			break;
		}
	}
	*list = list0 - 1;
	return (t_time);
}

/**
 * get_size - calculate size of arguments
 *
 * @format: string formated for args
 * @list: argument list
 *
 * Return: size(s)
 */

int get_size(const char *format, int *list)
{
	int list0 = *list + 1, s = 0;

	if (format[list0] == 'h')
		s = INT_SHORT;
	else if (format[list0] == 'l')
		s = INT_LONG;
	if (s == 0)
		*list = list0 - 1;
	else
		*list = list0;

	return (s);
}

/**
 * _width - finds the breadth of printing
 *
 * @format: formatted string
 * @list: arguments to be evaluated
 * @vl: list of arguments
 *
 * Return: width
 */

int _width(const char *format, int *list, va_list vl)
{
	int list0, width = 0;

	for (list0 = *list + 1; format[list0] != '\0'; list0++)
	{
		if (_digit(format[list0]))
		{
			width *= 10;
			width += format[list0] - '0';
		}
		else if (format[list0] == '*')
		{
			list0++;
			width = va_arg(vl, int);
			break;
		}
		else
		{
			break;
		}
	}
	*list = list0 - 1;
	return (width);
}

/**
 * _flags - checks for flags used
 *
 * @format: formatted string
 * @list: inputted parameter
 *
 * Return: flag
 */

int _flags(const char *format, int *list)
{
	int n, list0, flag = 0;

	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {FL_MINUS, FL_PLUS, FL_ZERO, FL_SHARP, FL_SPACE, 0};

	for (list0 = *list + 1; format[list0] != '\0'; list0++)
	{
		n = 0;

		for (n = 0; FLAGS_CHAR[n] != '\0'; n++)
		{
			if (format[list0] == FLAGS_CHAR[n])
			{
				flag |= FLAGS_ARRAY[n];
				break;
			}
		}
		if (FLAGS_CHAR[n] == 0)
			break;
	}
	*list = list0 - 1;
	return (flag);
}

/**
 * print_handler - prints the input
 *
 * @format: formatted string
 * @list: index
 * @buffer: buffer array fo print
 * @flag: checks for flags used
 * @vl: list of arguments
 * @width: breadth
 * @t_time: turn-around time
 * @size: size determiner
 *
 * Return: -1, or 1 or 2, or formatted types
 */
int print_handler(const char *format, int *list, va_list vl, char buffer[],
		int flag, int width, int t_time, int size)
{
	int index, len0 = 0, count_chars = -1;
	t_form _types[] = {
		{'c', _character}, {'s', _string}, {'%', _percentage},
		{'i', _integer}, {'d', _integer}, {'b', _binary},
		{'u', _unsigned}, {'o', _octal}, {'x', _hexadecimal},
		{'X', _hexadecimal_up}, {'p', _pointer}, {'S', _non_printable},
		{'r', _reverse}, {'R', _rot13}, {'\0', NULL}
	};

	for (index = 0; _types[index].format != '\0'; index++)
	{
		if (format[*list] == _types[index].format)
			return (_types[index].fxn(vl, buffer, flag, width, t_time, size));
	}
	if (_types[index].format == '\0')
	{
		if (format[*list] == '\0')
			return (-1);

		len0 += write(1, "%%", 1);
		if (format[*list - 1] == ' ')
			len0 += write(1, " ", 1);
		else if (width)
		{
			--(*list);
			while (format[*list] != ' ' && format[*list] != '%')
				--(*list);
			if (format[*list] == ' ')
				--(*list);
			return (1);
		}
		len0 += write(1, &format[*list], 1);
		return (len0);
	}
	return (count_chars);
}
