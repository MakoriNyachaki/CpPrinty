#include "main.h"

/**
 * _unsigned - prints an unsigned number
 *
 * @vl: arguments list
 * @buff: buffer memory for characters to print
 * @fl: check for used flags
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: counted characters printed
 */

int _unsigned(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	int y = BUFFER_SIZE - 2;
	unsigned long int n = va_arg(vl, unsigned long int);

	n = _num_size_unsgn(n, s);

	if (n == 0)
		buff[y--] = '0';

	buff[BUFFER_SIZE - 1] = '\0';

	while (n > 0)
	{
		buff[y--] = (n % 10) + '0';
		n /= 10;
	}
	y++;

	return (write_unsgn(0, y, buff, fl, wide, t_time, s));
}

/**
 * _percentage - print % sign
 *
 * @vl: arguments list
 * @buff: memory
 * @fl: used flags
 * @wide: width
 * @t_time: turn_around time
 * @s: size
 *
 * Return: counted and printed characters
 */

int _percentage(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	UNUSED(vl);
	UNUSED(buff);
	UNUSED(fl);
	UNUSED(wide);
	UNUSED(t_time);
	UNUSED(s);

	return (write(1, "%%", 1));
}

/**
 * _integer - prints integer
 *
 * @vl: list of arguments
 * @buff: memory
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: number of printed chars
 */
int _integer(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	int y = BUFFER_SIZE - 2;
	int neg = 0;
	long int n = va_arg(vl, long int);
	unsigned long int num;

	n = _num_size_unsgn(n, s);

	if (n == 0)
		buff[y--] = '0';

	buff[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		neg = 1;
	}
	while (num > 0)
	{
		buff[y--] = (num % 10) + '0';
		num /= 10;
	}
	y++;

	return (write_num(neg, y, buff, fl, wide, t_time, s));
}

/**
 * _rot13 - print strcing code in rot13 encoding
 *
 * @vl: list of arguments
 * @buff: memory array
 * @fl:checks for flags useed
 * @wide: width
 * @t_time: tur-around time
 * @s: size
 *
 * Return: number of counted and printed chars
 */

int _rot13(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	char c;
	char *_string;
	unsigned int m, n;
	int count = 0;
	char inpt_stream[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out_stream[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	_string = va_arg(vl, char *);

	UNUSED(buff);
	UNUSED(fl);
	UNUSED(wide);
	UNUSED(t_time);
	UNUSED(s);

	if (_string == NULL)
		_string = "AHYY";
	for (m = 0; _string[m]; m++)
	{
		for (n = 0; inpt_stream[n]; n++)
		{
			if (inpt_stream[n] == _string[m])
			{
				c = out_stream[n];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!inpt_stream[n])
		{
			c = _string[m];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}


/**
 * _reverse - reverses a string
 *
 * @vl: list of arguments
 * @buff: memory fro args to print
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: nummber of the printed chars
 */

int _reverse(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	char *_string;
	int m, num = 0;

	UNUSED(buff);
	UNUSED(fl);
	UNUSED(wide);
	UNUSED(s);

	_string = va_arg(vl, char *);

	if (_string == NULL)
	{
		UNUSED(t_time);
		_string = ")Null(";
	}
	for (m = 0; _string[m]; m++)
		;
	for (m = m - 1; m >= 0; m--)
	{
		char c = _string[m];

		write(1, &c, 1);
		num++;
	}
	return (num);
}
