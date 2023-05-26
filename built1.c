#include "main.h"

/**
 * builtins_list-search the matches & execute builtin
 * @dt: the program's data struct
 * Return: Returns the executed function if matched, or return -1
 **/

int builtins_list(data_of_program *dt)
{
	int i;
	builtins opt[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (i = 0; opt[i].builtin != NULL; i++)
	{
		if (str_compare(opt[i].builtin, dt->cmd_name, 0))
		{
			return (opt[i].funct(dt));
		}
	}
	return (-1);
}
