#include "main.h"

int check_file(char *full_path);

/**
 * find_program-finds program in path
 * @dt: program's data struct
 * Return: 0 if success, or err_code
 */

int find_program(data_of_program *dt)
{
	int i = 0, ret_code = 0;
	char **direcs;

	if (!dt->cmd_name)
		return (2);

	if (dt->cmd_name[0] == '/' || dt->cmd_name[0] == '.')
		return (check_file(dt->cmd_name));

	free(dt->tokens[0]);
	dt->tokens[0] = str_concat(str_duplicate("/"), dt->cmd_name);
	if (!dt->tokens[0])
		return (2);

	direcs = tokenize_path(dt);

	if (!direcs || !direcs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; direcs[i]; i++)
	{
		direcs[i] = str_concat(direcs[i], dt->tokens[0]);
		ret_code = check_file(direcs[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(dt->tokens[0]);
			dt->tokens[0] = str_duplicate(direcs[i]);
			free_array_of_pointers(direcs);
			return (ret_code);
		}
	}
	free(dt->tokens[0]);
	dt->tokens[0] = NULL;
	free_array_of_pointers(direcs);
	return (ret_code);
}

/**
 * tokenize_path-tokenize directories path
 * @dt: program's data struct
 * Return: array of path directories
 */

char **tokenize_path(data_of_program *dt)
{
	int count_direcs = 2;
	char **tokens = NULL;
	char *PATH;
	int i;

	PATH = env_get_key("PATH", dt);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_direcs++;
	}

	tokens = malloc(sizeof(char *) * count_direcs);

	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file-check if file exists, if it's not a dairectory and if it has
 * excecution permisions for it's permisions
 * @full_path: pointer to the full file name
 * Return: error code if exists, o success
 */

int check_file(char *full_path)
{
	struct stat x;

	if (stat(full_path, &x) != -1)
	{
		if (S_ISDIR(x.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
