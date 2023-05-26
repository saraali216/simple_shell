#include "main.h"

/**
 * str_length-gives the length of string
 * @ch: pointer to string
 * Return: length of string
 */

int str_length(char *ch)
{
	int l = 0;

	if (ch == NULL)
		return (0);

	while (ch[l++] != '\0')
	{
	}
	return (--l);
}

/**
 * str_duplicate-duplicate string
 * @ch: String to copy it
 * Return: pointer to array
 */

char *str_duplicate(char *ch)
{
	int i, l;
	char *resut;

	if (ch == NULL)
		return (NULL);

	l = str_length(ch) + 1;

	resut = malloc(sizeof(char) * l);

	if (resut == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < l ; i++)
	{
		resut[i] = ch[i];
	}

	return (resut);
}

/**
 * str_compare-compares 2 strings
 * @ch1: the short
 * @ch2: the long
 * @n: number of characters to compare them, 0 infinite
 * Return: 0 different strings, 1 equals
 */

int str_compare(char *ch1, char *ch2, int n)
{
	int i;

	if (ch1 == NULL && ch2 == NULL)
		return (1);

	if (ch1 == NULL || ch2 == NULL)
		return (0);

	if (n == 0)
	{
		if (str_length(ch1) != str_length(ch2))
			return (0);
		for (i = 0; ch1[i]; i++)
		{
			if (ch1[i] != ch2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < n ; i++)
		{
			if (ch1[i] != ch2[i])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat-concatenate 2 strings
 * @ch1: String to concateate it
 * @ch2: String to concatenate it
 * Return: pointer to array
 */

char *str_concat(char *ch1, char *ch2)
{
	int l1 = 0, l2 = 0;
	char *resut;

	if (ch1 == NULL)
		ch1 = "";
	l1 = str_length(ch1);

	if (ch2 == NULL)
		ch2 = "";
	l2 = str_length(ch2);

	resut = malloc(sizeof(char) * (l1 + l2 + 1));
	if (resut == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (l1 = 0; ch1[l1] != '\0'; l1++)
		resut[l1] = ch1[l1];
	free(ch1);

	for (l2 = 0; ch2[l2] != '\0'; l2++)
	{
		resut[l1] = ch2[l2];
		l1++;
	}

	resut[l1] = '\0';
	return (resut);
}


/**
 * str_reverse-reverses string
 * @ch: points to string.
 * Return: it's void
 */

void str_reverse(char *ch)
{

	int i = 0, l = str_length(ch) - 1;
	char hold;

	while (i < l)
	{
		hold = ch[i];
		ch[i++] = ch[l];
		ch[l--] = hold;
	}
}
