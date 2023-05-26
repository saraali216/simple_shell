#include "main.h"

/**
 * _strtok-separate strings with delimiters
 * @line: It´s pointer to array we receive in getline
 * @delim: It´s characters we mark off string in parts
 * Return: points to created token
*/

char *_strtok(char *line, char *delim)
{
	static char *xstr;
	char *copy_str;
	int j;

	if (line != NULL)
		xstr = line;
	for (; *xstr != '\0'; xstr++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*xstr == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	copy_str = xstr;
	if (*copy_str == '\0')
		return (NULL);
	for (; *xstr != '\0'; xstr++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*xstr == delim[j])
			{
				*xstr = '\0';
				xstr++;
				return (copy_str);
			}
		}
	}
	return (copy_str);
}
