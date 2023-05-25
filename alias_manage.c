#include "main.h"

/**
 * print_alias-show,remove,add aliases
 * @alias:name of alias that will be printed
 * @dt:struct of program's data
 * Return:0 sucess, or other number if its declared in the arguments
 */

int print_alias(data_of_program *dt, char *alias)
{
	int i, j, aliasl;
	char buff[250] = {'\0'};

	if (dt->alias_list)
	{
		aliasl = str_length(alias);
		for (i = 0; dt->alias_list[i]; i++)
		{
			if (!alias || (str_compare(dt->alias_list[i], alias, aliasl)
				&&	dt->alias_list[i][aliasl] == '='))
			{
				for (j = 0; dt->alias_list[i][j]; j++)
				{
					buff[j] = dt->alias_list[i][j];
					if (dt->alias_list[i][j] == '=')
						break;
				}
				buff[j + 1] = '\0';
				buffer_add(buff, "'");
				buffer_add(buff, dt->alias_list[i] + j + 1);
				buffer_add(buff, "'\n");
				_print(buff);
			}
		}
	}

	return (0);
}

/**
 * get_alias-show,remove,add aliases
 * @alias: alias's name
 * @dt:struct of program's data
 * Return:0 sucess, or other number if its declared in the arguments
 */

char *get_alias(data_of_program *dt, char *alias)
{
	int i, aliasl;

	if (alias == NULL || dt->alias_list == NULL)
		return (NULL);

	aliasl = str_length(alias);

	for (i = 0; dt->alias_list[i]; i++)
	{
		if (str_compare(alias, dt->alias_list[i], aliasl) &&
			dt->alias_list[i][aliasl] == '=')
		{
			return (dt->alias_list[i] + aliasl + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias-show,remove,add aliases
 * @alias_string: alias to seted in form
 * @dt:struct of program's data
 * Return:0 sucess, or other number if its declared in the arguments
 */

int set_alias(char *alias_string, data_of_program *dt)
{
	int i, j;
	char buff[250] = {'0'}, *tmp = NULL;

	if (alias_string == NULL ||  dt->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buff[i] = alias_string[i];
		else
		{
			tmp = get_alias(dt, alias_string + i + 1);
			break;
		}

	for (j = 0; dt->alias_list[j]; j++)
		if (str_compare(buff, dt->alias_list[j], i) &&
			dt->alias_list[j][i] == '=')
		{
			free(dt->alias_list[j]);
			break;
		}

	if (tmp)
	{
		buffer_add(buff, "=");
		buffer_add(buff, tmp);
		dt->alias_list[j] = str_duplicate(buff);
	}
	else
		dt->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
