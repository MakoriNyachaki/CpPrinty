#include "main.h"

/**
 * _digit - checks for numbers only
 *
 * @c: character to be checked
 *
 * Return: 1 if c is a digit and 0 otherwise
 */

int _digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * _printable - checks for a printable character
 *
 * @c: character to be evaluated
 *
 * Return: 1 if character is printable and
 * 0 otherwise
 */

int _printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

/**
 * _number_size - checks and set number to a given size
 *
 * @n: number to be evaluated
 * @s: type to be checked and ste
 *
 * Return: n
 *
 */

long int _number_size(int n, int s)
{
	if (s == INT_SHORT)
		return ((short)n);
	else if (s == INT_LONG)
		return (n);
	return ((int)n);
}

/**
 * _num_size_unsigned - checks for unsigned integers
 *
 * @n: number to be evaluated
 * @s: size to be set and checked for
 *
 * Return: number checked
 */

long int _num_size_unsgn(unsigned long int n, int s)
{
	if (s == INT_SHORT)
		return ((unsigned short)n);
	else if (s == INT_LONG)
		return (n);

	return ((unsigned int)n);
}

/**
 * _hexa_notation - set ASCII code notatipn in the buffer
 *
 * @ascii: ASCII code
 * @buffer: array of characters held in the buffer
 * @index: starting point
 *
 * Return: always 3
 *
 */

int _hexa_notation(char ascii, char buffer[], int index)
{
	char _hex[] = "0123456789ABCDEF";

	if (ascii < 0)
		ascii *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = _hex[ascii / 16];
	buffer[index] = _hex[ascii % 16];

	return (3);
}
