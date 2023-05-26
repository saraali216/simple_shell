#include "main.h"

/**
 * env_get_key-gets value of environmient variable
 * @k:environment variable key
 * @dt:program's data struct
 * Return: a pointer to the variable's value or NULL if it isn't not there
 */

char *env_get_key(char *k, data_of_program *dt)
{
	int i, keyl = 0;

	if (k == NULL || dt->env == NULL)
		return (NULL);

	keyl = str_length(k);

	for (i = 0; dt->env[i]; i++)
	{
		if (str_compare(k, dt->env[i], keyl) &&
		 dt->env[i][keyl] == '=')
		{
			return (dt->env[i] + keyl + 1);
		}
	}
	return (NULL);
}

/**
 * env_set_key - replace the environment variable's value
 * or make it if it's not there
 * @k: the variable to set
 * @val: new_value
 * @dt: program's data struct
 * Return: 0 success, 1 if parameters are NULL
 */

int env_set_key(char *k, char *val, data_of_program *dt)
{
	int i, keyl = 0, new_key = 1;

	if (k == NULL || val == NULL || dt->env == NULL)
		return (1);

	keyl = str_length(k);

	for (i = 0; dt->env[i]; i++)
	{
		if (str_compare(k, dt->env[i], keyl) &&
		 dt->env[i][keyl] == '=')
		{
			new_key = 0;
			free(dt->env[i]);
			break;
		}
	}
	dt->env[i] = str_concat(str_duplicate(k), "=");
	dt->env[i] = str_concat(dt->env[i], val);

	if (new_key)
	{
		dt->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key-remove key from the environment
 * @k:key to remove
 * @dt: program's data struct
 * Return: 0 key doesn't exist, 1 removed key
 */

int env_remove_key(char *k, data_of_program *dt)
{
	int i, keyl = 0;

	if (k == NULL || dt->env == NULL)
		return (0);

	keyl = str_length(k);

	for (i = 0; dt->env[i]; i++)
	{
		if (str_compare(k, dt->env[i], keyl) &&
		 dt->env[i][keyl] == '=')
		{
			free(dt->env[i]);

			i++;
			for (; dt->env[i]; i++)
			{
				dt->env[i - 1] = dt->env[i];
			}
			dt->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ-print current environ
 * @dt: program's data struct
 * Return: nthg
 */

void print_environ(data_of_program *dt)
{
	int j;

	for (j = 0; dt->env[j]; j++)
	{
		_print(dt->env[j]);
		_print("\n");
	}
}
