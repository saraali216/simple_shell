#include "main.h"

/**
 * main-initiate variables of program
 * @argc: number of values received from the cmndl
 * @argv: values received from the cmdl
 * @env: number of values received from the cmdl
 * Return: 0 on succes
 */

int main(int argc, char *argv[], char *env[])
{
	data_of_program dt_struct = {NULL}, *dt = &dt_struct;
	char *prmpt = "";

	inicialize_data(dt, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prmpt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prmpt, dt);
	return (0);
}

/**
 * handle_ctrl_c-prints prompt in new line when the signal
 * SIGINT (ctrl + c) is send to program
 * @UNUSED: prototype's option
 */

void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - initiate struct with the program's info
 * @dt: pointer to data struct
 * @argv: array of arguments passes to the program execution
 * @env: environ passes to the program execution
 * @argc: number of values received from the cmdl
 */

void inicialize_data(data_of_program *dt, int argc, char *argv[], char **env)
{
	int j = 0;

	dt->program_name = argv[0];
	dt->input_line = NULL;
	dt->cmd_name = NULL;
	dt->exec_counter = 0;
	if (argc == 1)
		dt->file_descript = STDIN_FILENO;
	else
	{
		dt->file_descript = open(argv[1], O_RDONLY);
		if (dt->file_descript == -1)
		{
			_printe(dt->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	dt->tokens = NULL;
	dt->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[j]; j++)
		{
			dt->env[j] = str_duplicate(env[j]);
		}
	}
	dt->env[j] = NULL;
	env = dt->env;

	dt->alias_list = malloc(sizeof(char *) * 20);
	for (j = 0; j < 20; j++)
	{
		dt->alias_list[j] = NULL;
	}
}

/**
 * sisifo-infinite loop to show prompt
 * @prompt: printed prompt
 * @dt: infinite loop that shows the prompt
 */

void sisifo(char *prompt, data_of_program *dt)
{
	int strl = 0, err_code = 0;

	while (++(dt->exec_count))
	{
		_print(prompt);
		err_code = strl = _getline(dt);

		if (err_code == EOF)
		{
			free_all_data(dt);
			exit(errno);
		}
		if (strl >= 1)
		{
			expand_alias(dt);
			expand_variables(dt);
			tokenize(dt);
			if (dt->tokens[0])
			{
				err_code = execute(dt);
				if (err_code != 0)
					_print_error(err_code, dt);
			}
			free_recurrent_data(dt);
		}
	}
}
