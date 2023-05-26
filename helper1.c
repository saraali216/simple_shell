#include "main.h"

/**
 * long_to_string-convert number to string
 * @n: number to convert to string
 * @ch: buffer to save the number as string coincidence
 * @base: base to convert number
 * Return: Nthg
 */

void long_to_string(long n, char *ch, int base)
{
	int i = 0, neg = 0;
	long cc = n;
	char letters[] = {"0123456789abcdef"};

	if (cc == 0)
		ch[i++] = '0';

	if (ch[0] == '-')
		neg = 1;

	while (cc)
	{
		if (cc < 0)
			ch[i++] = letters[-(cc % base)];
		else
			ch[i++] = letters[cc % base];
		cc /= base;
	}
	if (neg)
		ch[i++] = '-';

	ch[i] = '\0';
	str_reverse(ch);
}


/**
 * _atoi - convert a string to number
 * @s: pointer to str
 * Return: string's number or 0.
 */

int _atoi(char *s)
{
	int signe = 1;
	unsigned int n = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			signe *= -1;
		if (*s == '+')
			signe *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		n = (n * 10) + (*s - '0');
		s++;
	}
	return (n * signe);
}

/**
 * count_characters-counts the coincidences of string
 * @ch: points to str
 * @c:chars to be counted
 * Return: number of string or 0.
 */

int count_characters(char *ch, char *c)
{
	int i = 0, count = 0;

	for (; ch[i]; i++)
	{
		if (ch[i] == c[0])
			count++;
	}
	return (count);
}
