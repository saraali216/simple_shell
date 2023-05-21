#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <signal.h> 
#include <fcntl.h>
#include <string.h> 
#include <stddef.h>
#include <errno.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>

        /* OTHERS */

#include "others.h" 


        /* ALL-STRUCTURES */

/**
 * struct info- struct for the program's data
 * @program_name:name of executable
 * @cmd_name: pointer to the first cmd
 * @input_line: pointer to input read
 * @exec_count: number excecuted cmds
 * @file_descript: file descripionr to the input of cmds
 * @tokens: pointer to array of the inputs that tokenized
 * @env: copy of environ
 * @alias_list: array of pointers of aliases
 */
typedef struct info
{
	char *program_name;
	char *cmd_name;
	char input_line;
	int exec_count;
	int file_descript;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins-builtins struct
 * @builtin:name of builtin
 * @funct: associated function to call it for every builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*funct)(data_of_program *dt);
} builtins;



        /* builtins_more.c */

int builtin_exit(data_of_program *dt);
int builtin_cd(data_of_program *dt);
int set_work_directory(data_of_program *dt, char *new_dir);
int builtin_help(data_of_program *dt);
int builtin_alias(data_of_program *dt);


        /* builtins_env.c */

int builtin_env(data_of_program *dt);
int builtin_set_env(data_of_program *dt);
int builtin_unset_env(data_of_program *dt);



        /* env_management.c */

char *env_get_key(char *k, data_of_program *dt);
int env_set_key(char *k, char *val, data_of_program *dt);
int env_remove_key(char *k, data_of_program *dt);
void print_environ(data_of_program *dt);



        /*  main.c  */

void inicialize_data(data_of_program *dt, int argc, char *argv[], char **env);
void sisifo(char *prompt, data_of_program *dt);
void handle_ctrl_c(int opr UNUSED);


        /*  _getline.c  */

int _getline(data_of_program *dt);
int check_logic_ops(char *array_cmds[], int i, char array_opr[]);


        /* expand.c */

void expand_variables(data_of_program *dt);
void expand_alias(data_of_program *dt);
int buffer_add(char *buffer, char *str_add);


        /* tokens.c */

void tokenize(data_of_program *dt);
char *_strtok(char *line, char *delim);


        /* exec.c */

int execute(data_of_program *dt);


        /* builtins_list.c */

int builtins_list(data_of_program *dt);


        /* find_in_path.c */

char **tokenize_path(data_of_program *dt);
int find_program(data_of_program *dt);



        /* helpers_free.c */

void free_array_of_pointers(char **dirs);
void free_recurrent_data(data_of_program *dt);
void free_all_data(data_of_program *dt);



        /* helpers_string.c */

int str_length(char *ch);
char *str_duplicate(char *ch);
int str_compare(char *ch1, char *ch2, int n);
char *str_concat(char *ch1, char *ch2);
void str_reverse(char *ch);


        /* helpers_numbers.c */

void long_to_string(long n, char *ch, int base);
int _atoi(char *s);
int count_characters(char *ch, char *c);


        /* alias_management.c */

int print_alias(data_of_program *dt, char *alias);
char *get_alias(data_of_program *dt, char *alias);
int set_alias(char *alias_string, data_of_program *dt);


        /* helpers_print.c */

int _print(char *ch);
int _printe(char *ch);
int _print_error(int errorcode, data_of_program *dt);


#endif /* MAIN_H */
