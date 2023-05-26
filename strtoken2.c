#include "main.h"

/**
 * tokenize-separates the string using a designed delimiter
 * @dt: program's data struct
 * Return: array of the different parts of string
 */

void tokenize(data_of_program *dt)
{
	char *dlm = " \t";
	int i, j, count = 2, l;

	l = str_length(dt->input_line);
	if (l)
	{
		if (dt->input_line[l - 1] == '\n')
			dt->input_line[l - 1] = '\0';
	}

	for (i = 0; dt->input_line[i]; i++)
	{
		for (j = 0; dlm[j]; j++)
		{
			if (dt->input_line[i] == dlm[j])
				count++;
		}
	}

	dt->tokens = malloc(count * sizeof(char *));
	if (dt->tokens == NULL)
	{
		perror(dt->program_name);
		exit(errno);
	}
	i = 0;
	dt->tokens[i] = str_duplicate(_strtok(dt->input_line, dlm));
	dt->cmd_name = str_duplicate(dt->tokens[0]);
	while (dt->tokens[i++])
	{
		dt->tokens[i] = str_duplicate(_strtok(NULL, dlm));
	}
}
