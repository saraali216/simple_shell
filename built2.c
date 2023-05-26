#include "main.h"

/**
 * builtin_exit-exit of the program and the status
 * @dt:program's data struct
 * Return: 0 sucess, other number if fails
 */

int builtin_exit(data_of_program *dt)
{
	int i;

	if (dt->tokens[1] != NULL)
	{
		for (i = 0; dt->tokens[1][i]; i++)
			if ((dt->tokens[1][i] < '0' || dt->tokens[1][i] > '9')
				&& dt->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(dt->tokens[1]);
	}
	free_all_data(dt);
	exit(errno);
}

/**
 * builtin_cd-change current directory
 * @dt:program's data struct
 * Return: 0 sucess, other number if fails
 */

int builtin_cd(data_of_program *dt)
{
	char *dir_hm = env_get_key("HOME", dt), *dir_old = NULL;
	char old_dir[128] = {0};
	int errc = 0;

	if (dt->tokens[1])
	{
		if (str_compare(dt->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", dt);
			if (dir_old)
				errc = set_work_directory(dt, dir_old);
			_print(env_get_key("PWD", dt));
			_print("\n");

			return (errc);
		}
		else
		{
			return (set_work_directory(dt, dt->tokens[1]));
		}
	}
	else
	{
		if (!dir_hm)
			dir_hm = getcwd(old_dir, 128);

		return (set_work_directory(dt, dir_hm));
	}
	return (0);
}

/**
 * set_work_directory-set work directory
 * @dt:program's data struct
 * @new_dir: path to set it as working directory
 * Return:0 sucess, other number if fails
 */

int set_work_directory(data_of_program *dt, char *new_dir)
{
	char old_dir[128] = {0};
	int errc = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		errc = chdir(new_dir);
		if (errc == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, dt);
	}
	env_set_key("OLDPWD", old_dir, dt);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell is working
 * @dt:program's data struct
 * Return:0 sucess, other number if fails
 */

int builtin_help(data_of_program *dt)
{
	int i, l = 0;
	char *mnsjs[6] = {NULL};

	mnsjs[0] = HELP_MSG;

	if (dt->tokens[1] == NULL)
	{
		_print(mnsjs[0] + 6);
		return (1);
	}
	if (dt->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(dt->cmd_name);
		return (5);
	}
	mnsjs[1] = HELP_EXIT_MSG;
	mnsjs[2] = HELP_ENV_MSG;
	mnsjs[3] = HELP_SETENV_MSG;
	mnsjs[4] = HELP_UNSETENV_MSG;
	mnsjs[5] = HELP_CD_MSG;

	for (i = 0; mnsjs[i]; i++)
	{
		l = str_length(dt->tokens[1]);
		if (str_compare(dt->tokens[1], mnsjs[i], l))
		{
			_print(mnsjs[i] + l + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(dt->cmd_name);
	return (0);
}

/**
 * builtin_alias-show,remove,add aliases
 * @dt:program's data struct
 * Return:0 sucess, other number if fails
 */

int builtin_alias(data_of_program *dt)
{
	int i = 0;

	if (dt->tokens[1] == NULL)
		return (print_alias(dt, NULL));

	while (dt->tokens[++i])
	{
		if (count_characters(dt->tokens[i], "="))
			set_alias(dt->tokens[i], dt);
		else
			print_alias(dt, dt->tokens[i]);
	}

	return (0);
}

