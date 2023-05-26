#include "main.h"

/**
 * expand_variables -expand variables
 * @data:program's data struct
 * Return: nothing, sets errno.
 */

void expand_variables(data_of_program *data)
{
	int i, j;
	/* char input_line = dt->input_line */
	char ln[BUFFER_SIZE] = {0}, expsn[BUFFER_SIZE] = {'\0'}, *tmp;

	if (!data->input_line)
		return;
	buffer_add(ln, data->input_line);
	for (i = 0; ln[i]; i++)
		if (ln[i] == '#')
			ln[i--] = '\0';
		else if (ln[i] == '$' && ln[i + 1] == '?')
		{
			ln[i] = '\0';
			long_to_string(errno, expsn, 10);
			buffer_add(ln, expsn);
			buffer_add(ln, data->input_line + i + 2);
		}
		else if (ln[i] == '$' && ln[i + 1] == '$')
		{
			ln[i] = '\0';
			long_to_string(getpid(), expsn, 10);
			buffer_add(ln, expsn);
			buffer_add(ln, data->input_line + i + 2);
		}
		else if (ln[i] == '$' && (ln[i + 1] == ' ' || ln[i + 1] == '\0'))
			continue;
		else if (ln[i] == '$')
		{
			for (j = 1; ln[i + j] && ln[i + j] != ' '; j++)
				expsn[j - 1] = ln[i + j];
			tmp = env_get_key(expsn, data);
			ln[i] = '\0', expsn[0] = '\0';
			buffer_add(expsn, ln + i + j);
			tmp ? buffer_add(ln, tmp) : 1;
			buffer_add(ln, expsn);
		}
	if (!str_compare(data->input_line, ln, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(ln);
	}
}

/**
 * expand_alias-expand aliases
 * @dt: program's data struct
 * Return: nothing, set errno.
 */

void expand_alias(data_of_program *dt)
{
	int i, j, prv_expand = 0;
	char ln[BUFFER_SIZE] = {0}, expsn[BUFFER_SIZE] = {'\0'}, *tmp;

	if (dt->input_line == NULL)
		return;

	buffer_add(ln, dt->input_line);

	for (i = 0; ln[i]; i++)
	{
		for (j = 0; ln[i + j] && ln[i + j] != ' '; j++)
			expsn[j] = ln[i + j];
		expsn[j] = '\0';

		tmp = get_alias(dt, expsn);
		if (tmp)
		{
			expsn[0] = '\0';
			buffer_add(expsn, ln + i + j);
			ln[i] = '\0';
			buffer_add(ln, tmp);
			ln[str_length(ln)] = '\0';
			buffer_add(ln, expsn);
			prv_expand = 1;
		}
		break;
	}
	if (prv_expand)
	{
		free(dt->input_line);
		dt->input_line = str_duplicate(ln);
	}
}

/**
 * buffer_add-add string at end of buffer
 * @buffer: buffer will be filled
 * @str_add: string tocopy it in buffer
 * Return: nthg, sets errno
 */

int buffer_add(char *buffer, char *str_add)
{
	int l, i;

	l = str_length(buffer);
	for (i = 0; str_add[i]; i++)
	{
		buffer[l + i] = str_add[i];
	}
	buffer[l + i] = '\0';
	return (l + i);
}
