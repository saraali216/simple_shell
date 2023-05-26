#include "main.h"

/**
 * builtin_env-Builtin environment where the shell will be working
 * @dt: program's data struct
 * Return: 0 sucess, another value if fails
 */

int builtin_env(data_of_program *dt)
{
	int i;
	char cpn[50] = {'\0'};
	char *varcp = NULL;

	if (dt->tokens[1] == NULL)
		print_environ(dt);
	else
	{
		for (i = 0; dt->tokens[1][i]; i++)
		{
			if (dt->tokens[1][i] == '=')
			{
				varcp = str_duplicate(env_get_key(cpn, dt));
				if (varcp != NULL)
					env_set_key(cpn, dt->tokens[1] + i + 1, dt);

				print_environ(dt);
				if (env_get_key(cpn, dt) == NULL)
				{
					_print(dt->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cpn, varcp, dt);
					free(varcp);
				}
				return (0);
			}
			cpn[i] = dt->tokens[1][i];
		}
		errno = 2;
		perror(dt->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - setting builtin environment
 * @dt: program's data struct
 * Return: 0 sucess, another value if fails
 */

int builtin_set_env(data_of_program *dt)
{
	if (dt->tokens[1] == NULL || dt->tokens[2] == NULL)
		return (0);
	if (dt->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(dt->cmd_name);
		return (5);
	}

	env_set_key(dt->tokens[1], dt->tokens[2], dt);

	return (0);
}

/**
 * builtin_unset_env - unsetting builtin environment
 * @dt: program's data struct
 * Return: 0 succes, another value if fails
 */

int builtin_unset_env(data_of_program *dt)
{
	if (dt->tokens[1] == NULL)
		return (0);
	if (dt->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(dt->cmd_name);
		return (5);
	}
	env_remove_key(dt->tokens[1], dt);

	return (0);
}
