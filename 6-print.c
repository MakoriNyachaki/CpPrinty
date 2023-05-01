#include "main.h"

/**
 * write_pointer - writes to a memory address
 *
 * @buff: memory buffer
 * @index: index of the beginning of the buffer
 * @len: size of number
 * @wide: width
 * @fl: flsgs used
 * @spc: character fo padding
 * @ex: extra character
 * @spc_strt: statr of padding
 *
 * Return: count characters written
 */

int write_pointer(char buff[], int index, int len, int wide,
		int fl, char spc, char ex, int spc_strt)
{
	int n = 0;

	if (wide > len)
	{
		for (; n < wide - len; n++)
			buff[n] = spc;
		buff[n] = '\0';
		if (fl & FL_MINUS && spc == ' ')
		{
			buff[--index] = 'x';
			buff[--index] = '0';
			if (ex)
				buff[--index] = ex;
			return (write(1, &buff[index], len) + write(1, &buff[3], n - 3));
		}
		else if (!(fl & FL_MINUS) && spc == ' ')
		{
			buff[--index] = 'x';
			buff[--index] = '0';
			if (ex)
				buff[--index] = ex;
			return (write(1, &buff[3], n - 3) + write(1, &buff[index], len));
		}
		else if (!(fl & FL_MINUS) && spc == '0')
		{
			if (ex)
				buff[--spc_strt] = ex;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[spc_strt], n - spc_strt) +
					write(1, &buff[index], len - (1 - spc_strt) - 2));
		}
	}
	buff[--index] = 'x';
	buff[--index] = '0';

	if (ex)
		buff[--index] = ex;
	return (write(1, &buff[index], BUFFER_SIZE - index - 1));
}


/**
 * write_unsigned - prints unsigned number
 *
 * @neg: checks for negative number
 * @index: index of the beginning of the buffer
 * @buff: memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: count of characters written
 */

int write_unsgn(int neg, int index, char buff[], int fl,
		int wide, int t_time, int s)
{
	int len, n;
	char spc = ' ';

	len = BUFFER_SIZE - index - 1;
	n = 0;

	UNUSED(neg);
	UNUSED(s);

	if (t_time == 0 && index == BUFFER_SIZE - 2 && buff[index] == '0')
		return (0);
	if (t_time > 0 && t_time < len)
		spc = ' ';
	while (t_time > len)
	{
		buff[--index] = '0';
		len++;
	}
	if ((fl & FL_ZERO) && !(fl & FL_MINUS))
		spc = '0';
	if (wide > len)
	{
		for (n = 0; n < wide - len; n++)
			buff[n] = spc;

		buff[n] = '\0';

		if (fl & FL_MINUS)
		{
			return (write(1, &buff[index], len) +
					write(1, &buff[0], n));
		}
		else
		{
			return (write(1, &buff[0], n) +
					write(1, &buff[index], len));
		}
	}
	return (write(1, &buff[index], len));
}

/**
 * write_char - print a character string
 *
 * @c: character
 * @buff: memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: number of chars written
 */

int write_char(char c, char buff[], int fl, int wide,
		int t_time, int s)
{
	int n = 0;
	char spc = ' ';

	UNUSED(t_time);
	UNUSED(s);

	if (fl & FL_ZERO)
		spc = '0';

	buff[n++] = c;
	buff[n] = '\0';

	if (wide > 1)
	{
		buff[BUFFER_SIZE - 1] = '\0';
		for (n = 0; n < wide - 1; n++)
			buff[BUFFER_SIZE - n - 2] = spc;
		if (fl & FL_MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFFER_SIZE - n - 1], wide - 1));
		else
			return (write(1, &buff[BUFFER_SIZE - n - 1], wide - 1) +
					write(1, &buff[0], 1));
	}
	return (write(1, &buff[0], 1));
}

/**
 * write_num - prints a  number
 *
 * @neg: checks for negative numbers
 * @index: starting index of buff
 * @buff: memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @s: size
 *
 * Return: count
 */

int write_num(int neg, int index, char buff[], int fl,
		int wide, int t_time, int s)
{
	int len = BUFFER_SIZE - index - 1;
	char spc = ' ', ex = 0;

	UNUSED(s);

	if ((fl & FL_ZERO) && !(fl & FL_MINUS))
		spc = '0';
	if (neg)
		ex = '-';
	else if (fl & FL_PLUS)
		ex = '+';
	else if (fl & FL_SPACE)
		ex = ' ';

	return (_number(index, buff, fl, wide, t_time,
				len, spc, ex));
}

/**
 * _number - write a number
 *
 * @index: first buffer element index
 * @buff: memory buffer
 * @fl: flags used
 * @wide: width
 * @t_time: turn-around time
 * @len: length
 * @spc: padding
 * @ex: Extra character
 *
 * Return: number
 */
int _number(int index, char buff[], int fl, int wide,
		int t_time, int len, char spc, char ex)
{
	int n, spc_strt = 1;

	if (t_time == 0 && index == BUFFER_SIZE - 2 &&
			buff[index] == '0' && wide == 0)
	return (0);
	if (t_time == 0 && index == BUFFER_SIZE - 2 && buff[index] == '0')
		buff[index] = spc = ' ';
	if (t_time > 0 && t_time < len)
		spc = ' ';
	while (t_time > len)
		buff[--index] = '0', len++;
	if (ex != 0)
		len++;
	if (wide > len)
	{
		for (n = 1; n < wide - len + 1; n++)
			buff[n] = spc;
		buff[n] = '\0';
		if (fl & FL_MINUS && spc == ' ')
		{
			if (ex)
				buff[--index] = ex;
			return (write(1, &buff[index], len) + write(1, &buff[1], n - 1));
		}
		else if (!(fl & FL_MINUS) && spc == ' ')
		{
			if (ex)
				buff[--index] = ex;
			return (write(1, &buff[1], n - 1) + write(1, &buff[index], len));
		}
		else if (!(fl & FL_MINUS) && spc == '0')
		{
			if (ex)
				buff[--spc_strt] = ex;
			return (write(1, &buff[spc_strt], n - spc_strt) +
					write(1, &buff[index], len - (1 - spc_strt)));
		}
	}
	if (ex)
		buff[--index] = ex;
	return (write(1, &buff[index], len));
}
