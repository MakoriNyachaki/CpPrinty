#include "main.h"

/**
 * _string - prints a string
 *
 * @vl: list of arguments
 * @buff: memory buffer
 * @fl: used flags
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: counted printed chars
 */

int _string(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	int len = 0, i;
	char *_string = va_arg(vl, char *);

	UNUSED(buff);
	UNUSED(fl);
	UNUSED(wide);
	UNUSED(t_time);
	UNUSED(s);

	if (_string == NULL)
	{
		_string = "Empty";
		if (t_time >= 6)
			_string = " ";
	}
	while (_string[len] != '\0')
		len++;

	if (t_time >= 0 && t_time < len)
		len = t_time;

	if (len < wide)
	{
		if (fl && FL_MINUS)
		{
			write(1, &_string[0], len);
			for (i = wide - len; i > 0; i--)
				write(1, " ", 1);
			return (wide);
		}
		else
		{
			for (i = wide - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &_string[0], len);
			return (wide);
		}
	}
	return (write(1, _string, len));
}

/**
 * _character - prints a character
 * @vl: list of arguments
 * @buff:memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn_around time
 * @s: size
 *
 * Return: counted printed chars
 */

int _character(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	char c;

	c = va_arg(vl, int);

	return (write_char(c, buff, fl, wide, t_time, s));
}

/**
 * _pointer - prints pointer value
 *
 * @vl: list of arguments
 * @buff: memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: number of chars printed
 */

int _pointer(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	char ex = 0, spc = ' ';
	int index, len, spc_strt;
	unsigned long address;
	char ptr_to[] = "0123456789abcdef";
	void *address1 = va_arg(vl, void *);

	index = BUFFER_SIZE - 2;
	len = 2;
	spc_strt = 1;

	UNUSED(wide);
	UNUSED(s);

	if (address1 == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFFER_SIZE - 1] = '\0';
	UNUSED(t_time);

	address = (unsigned long)address1;

	while (address > 0)
	{
		buff[index--] = ptr_to[address % 16];
		address /= 16;
		len++;
	}

	if ((fl & FL_ZERO) && !(fl & FL_MINUS))
		spc = '0';
	if (fl & FL_PLUS)
		ex = '+', len++;
	else if (fl & FL_SPACE)
		ex = ' ', len++;

	index++;

	return (write_pointer(buff, index, len, wide,
				fl, spc, ex, spc_strt));
}

/**
 * _non_printable - prints ASCII codes in hexa format
 * for characters not printable
 *
 * @vl: arguments list
 * @buff: memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: count of chars printed
 */

int _non_printable(va_list vl, char buff[], int fl, int wide,
		int t_time, int s)
{
	int n = 0, x = 0;

	char *_string;

	_string = va_arg(vl, char *);

	UNUSED(fl);
	UNUSED(wide);
	UNUSED(t_time);
	UNUSED(s);

	if (_string == NULL)
		return (write(1, "(null)", 6));

	while (_string[n] != '\0')
	{
		if (_printable(_string[n]))
			buff[n + x] = _string[n];
		else
			x += _hexa_notation(_string[n], buff, n + x);
		n++;
	}
	buff[n + x] = '\0';

	return (write(1, buff, n + x));
}
