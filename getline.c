#include "main.h"

/**
* _getline-read 1 line from the prompt
* @dt:program's data struct
* Return: count and read bytes
*/

int _getline(data_of_program *dt)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_cmds[10] = {NULL};
	static char array_opr[10] = {'\0'};
	ssize_t rbytes, i = 0;

	if (!array_cmds[0] || (array_opr[0] == '&' && errno != 0) ||
		(array_opr[0] == '|' && errno == 0))
	{
		for (i = 0; array_cmds[i]; i++)
		{
			free(array_cmds[i]);
			array_cmds[i] = NULL;
		}

		rbytes = read(dt->file_descript, &buff, BUFFER_SIZE - 1);
		if (rbytes == 0)
			return (-1);

		i = 0;
		do {
			array_cmds[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			i = check_logic_ops(array_cmds, i, array_opr);
		} while (array_cmds[i++]);
	}

	dt->input_line = array_cmds[0];
	for (i = 0; array_cmds[i]; i++)
	{
		array_cmds[i] = array_cmds[i + 1];
		array_opr[i] = array_opr[i + 1];
	}

	return (str_length(dt->input_line));
}


/**
* check_logic_ops-split & check for && and || operators
* @array_cmds: array of cmds
* @array_opr: array of logical operators of previous cmd
* @i:index of array_cmds to check it
* Return: i of the last cmd in array_cmds.
*/

int check_logic_ops(char *array_cmds[], int i, char array_opr[])
{
	char *tmp = NULL;
	int j;

	for (j = 0; array_cmds[i] != NULL  && array_cmds[i][j]; j++)
	{
		if (array_cmds[i][j] == '&' && array_cmds[i][j + 1] == '&')
		{
			tmp = array_cmds[i];
			array_cmds[i][j] = '\0';
			array_cmds[i] = str_duplicate(array_cmds[i]);
			array_cmds[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			array_opr[i] = '&';
			free(tmp);
			j = 0;
		}
		if (array_cmds[i][j] == '|' && array_cmds[i][j + 1] == '|')
		{
			tmp = array_cmds[i];
			array_cmds[i][j] = '\0';
			array_cmds[i] = str_duplicate(array_cmds[i]);
			array_cmds[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			array_opr[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}
