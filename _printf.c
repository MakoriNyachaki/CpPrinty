#include "main.h"

/**
 * _buffer - print contents of the buffer
 * @buffer: charcter array
 * @index: index for the  next character
 *
 * Return: nothing
 */

void _buffer(char buffer[], int *index)
{
	if (*index > 0)
		write(1, &buffer[0], *index);
	*index = 0;
}

/**
 * _printf - produces output according to a format
 *
 * @format: pointer to string
 *
 * Return: number of characters printed
 */

int _printf(const char *format, ...)
{
	va_list pa;
	int i, count_chars = 0, ind = 0;
	int fl, breadth, pre, size, b_ind = 0;
	char buff[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(pa, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			_buffer(buff, &b_ind);
			fl = _flags(format, &i);
			breadth = _width(format, &i, pa);
			pre = _precision(format, &i, pa);
			size = get_size(format, &i);
			++i;
			ind = print_handler(format, &i, pa, buff,
					fl, breadth, pre, size);
			if (ind == -1)
				return (-1);
			count_chars += ind;
		}
		else
		{
			buff[b_ind++] = format[i];
			if (b_ind == BUFFER_SIZE)
				_buffer(buff, &b_ind);
			count_chars++;
		}
	}
	_buffer(buff, &b_ind);

	va_end(pa);
	return (count_chars);
}
