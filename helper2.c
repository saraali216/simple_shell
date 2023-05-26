#include "main.h"

/**
 * _print-writes array of chars in the output
 * @ch: pointer to array of chars
 * Return: the amount of data written or an error Errno is set properly
 * and -1 is returned
 */

int _print(char *ch)
{
	return (write(STDOUT_FILENO, ch, str_length(ch)));
}

/**
 * _printe-writes array of chars in the output
 * @ch: pointer to array of chars
 * Return: the amount of data written or an error Errno is set properly
 * and -1 is returned
 */

int _printe(char *ch)
{
	return (write(STDERR_FILENO, ch, str_length(ch)));
}

/**
 * _print_error-writes array of chars
 * @dt:program's data struct
 * @errorcode: error code to print it
 * Return:the amount of data written or an error Errno is set properly
 * and -1 is returned
 */

int _print_error(int errorcode, data_of_program *dt)
{
	char nstr[10] = {'\0'};

	long_to_string((long) dt->exec_count, nstr, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(dt->program_name);
		_printe(": ");
		_printe(nstr);
		_printe(": ");
		_printe(dt->tokens[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(dt->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(dt->program_name);
		_printe(": ");
		_printe(nstr);
		_printe(": ");
		_printe(dt->cmd_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(dt->program_name);
		_printe(": ");
		_printe(nstr);
		_printe(": ");
		_printe(dt->cmd_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
