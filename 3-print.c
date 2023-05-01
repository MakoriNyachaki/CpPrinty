#include "main.h"


/**
 * _hexa_lower - prints in either lower or
 * upper hexadecimal notation
 *
 * @vl: list of arguments
 * @hex_to: hexadecimsl values
 * @buff: memory storage
 * @fl: checks for flags used
 * @fl_char: flag character used
 * @wide: width
 * @t_time: turn_around time
 * @s: size
 *
 * Return: count of printed chars
 */

int _hex_low_up(va_list vl, char hex_to[], char buff[], int fl,
		char fl_char, int wide, int t_time, int s)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int n, num;

	n = va_arg(vl, unsigned long int);
	num = n;

	UNUSED(wide);

	n = _num_size_unsgn(n, s);

	if (n == 0)
		buff[i--] = '0';

	buff[BUFFER_SIZE - 1] = '\0';
	while (n > 0)
	{
		buff[i--] = hex_to[n % 16];
		n /= 16;
	}
	if (fl & FL_SHARP && num != 0)
	{
		buff[i--] = fl_char;
		buff[i--] = '0';
	}

	i++;

	return (write_unsgn(0, i, buff, fl, wide, t_time, s));
}

/**
 * _hexadecimal -  converts in lower hexa and
 * prints in hexa notation
 *
 * @vl: list of arguments
 * @buff: memory to store args for print
 * @fl: checks for flags used
 * @width: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return:  counted chars printed
 */

int _hexadecimal(va_list vl, char buff[], int fl,
		int width, int t_time, int s)
{
	return (_hex_low_up(vl, "0123456789abcdef", buff, fl, 'x', width,
				t_time, s));
}


/**
 * _hexadecimal -  converts in upper hexa and
 * prints in hexa notation
 * @vl: list of arguments
 * @buff: memory to store args for print
 * @fl: checks for flags used
 * @width: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return:  counted chars printed
 */

int _hexadecimal_up(va_list vl, char buff[], int fl,
		int width, int t_time, int s)
{
	return (_hex_low_up(vl, "0123456789ABCDEF", buff, fl, 'X',
				width, t_time, s));
}

/**
 * _octal - prints unsigned ocatl number
 *
 * @vl: list of arguments
 * @buff: memory for buffer
 * @fl: checks for flags used
 * @wide: width
 * @t_time: turn_arounf time
 * @s: size
 *
 * Return: count of printed characters
 */

int _octal(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	int p = BUFFER_SIZE - 2;
	unsigned long int n = va_arg(vl, unsigned long int);
	unsigned long int num = n;

	UNUSED(wide);

	n = _num_size_unsgn(n, s);

	if (n == 0)
		buff[p--] = '0';

	buff[BUFFER_SIZE - 1] = '\0';

	while (n > 0)
	{
		buff[p--] = (n % 8) + '0';
		n /= 8;
	}

	if (fl & FL_SHARP && num != 0)
		buff[p--] = '0';

	p++;
	return (write_unsgn(0, p, buff, fl, wide, t_time, s));
}

/**
 * _binary - prints unsigned binary
 *
 * @vl: list of arguments
 * @buff: memory for print args
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: count of printed characters
 */

int _binary(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	unsigned int p, q, n, total;
	int count;

	unsigned int c[32];

	UNUSED(buff);
	UNUSED(fl);
	UNUSED(wide);
	UNUSED(t_time);
	UNUSED(s);

	p = va_arg(vl, unsigned int);
	q = 2147483648; /* 2 raised to power of 31 */
	c[0] = p / q;

	for (n = 1; n < 32; n++)
	{
		q /= 2;
		c[n] = (p / q) % 2;
	}
	for (n = 0, total = 0, count = 0; n < 32; n++)
	{
		total += c[n];
		if (total || n == 31)
		{
			char m = '0' + c[n];

			write(1, &m, 1);
			count++;
		}
	}
	return (count);
}
