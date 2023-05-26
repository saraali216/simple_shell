#include "main.h"

/**
 * free_recurrent_data-free fields needed for every loop
 * @dt:program's data struct
 * Return: Nthg
 */

void free_recurrent_data(data_of_program *dt)
{
	if (dt->tokens)
		free_array_of_pointers(dt->tokens);
	if (dt->input_line)
		free(dt->input_line);
	if (dt->cmd_name)
		free(dt->cmd_name);

	dt->input_line = NULL;
	dt->cmd_name = NULL;
	dt->tokens = NULL;
}

/**
 * free_all_data-free all fields of data
 * @dt:program's data struct
 * Return: Nthg
 */

void free_all_data(data_of_program *dt)
{
	if (dt->file_descript != 0)
	{
		if (close(dt->file_descript))
			perror(dt->program_name);
	}
	free_recurrent_data(dt);
	free_array_of_pointers(dt->env);
	free_array_of_pointers(dt->alias_list);
}

/**
 * free_array_of_pointers-releases each pointer in array of pointers
 * as well as the entire array
 * @dirs: array of pointers
 * Return: nothing
 */

void free_array_of_pointers(char **dirs)
{
	int i;

	if (dirs != NULL)
	{
		for (i = 0; dirs[i]; i++)
			free(dirs[i]);

		free(dirs);
		dirs = NULL;
	}
}
