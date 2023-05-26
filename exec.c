#include "main.h"

/**
 * execute-execute cmd with its path variables
 * @dt: the program's data struct/pointer
 * Return: 0 sucess, or return -1.
 */

int execute(data_of_program *dt)
{
	int rtval = 0, status;
	pid_t pidd;

	rtval = builtins_list(dt);
	if (rtval != -1)
		return (rtval);

	rtval = find_program(dt);
	if (rtval)
	{
		return (rtval);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(dt->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			rtval = execve(dt->tokens[0], dt->tokens, dt->env);
			if (rtval == -1)
				perror(dt->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
