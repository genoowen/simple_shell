#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/************* MACROS **************/

#include "macros.h"

/************* STRUCTURES **************/

typedef struct info
{
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} data_of_program;

typedef struct builtin
{
    char *builtin;
    int (*function)(data_of_program *data);
} builtins;

/************* MAIN FUNCTIONS *************/

void initialize_data(data_of_program *data, int argc, char *argv[], char **env);
void sisifo(char *prompt, data_of_program *data);
void handle_ctrl_c(int opr UNUSED);

/************* _getline.c *************/

int _getline(data_of_program *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/************* expansions.c *************/

void expand_variables(data_of_program *data);
void expand_alias(data_of_program *data);
int buffer_add(char *buffer, char *str_to_add);

/************* str_tok.c *************/

void tokenize(data_of_program *data);
char *_strtok(char *line, char *delim);

/************* execute.c *************/

int execute(data_of_program *data);

/************* builtins_list.c *************/

int builtin_list(data_of_program *data);

/************* find_in_path.c *************/

char **tokenize_path(data_of_program *data);
int find_program(data_of_program *data);

/************* HELPERS FOR MEMORY MANAGEMENT *************/

void free_array_of_pointers(char **directories);
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);

/************* BUILTINS *************/

int custom_builtin_env(data_of_program *data);
int custom_builtin_set_env(data_of_program *data);
int custom_builtin_unset_env(data_of_program *data);
int custom_builtin_exit(data_of_program *data);
int custom_builtin_cd(data_of_program *data);
int custom_builtin_help(data_of_program *data);
int custom_builtin_alias(data_of_program *data);

/************* HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT *************/

char *env_get_key(char *name, data_of_program *data);
int env_set_key(char *key, char *value, data_of_program *data);
int env_remove_key(char *key, data_of_program *data);
void print_environ(data_of_program *data);

/************* HELPERS FOR PRINTING *************/

int custom_print(char *string);
int custom_print_error(int errorcode, data_of_program *data);

/************* HELPERS FOR STRINGS MANAGEMENT *************/

int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_reverse(char *string);

int count_characters(char *string, char *character);

int count_characters(char *string, char *character);

int count_characters(char *string, char *character);

int count_characters(char *string, char *character);

/************* ALIAS MANAGEMENT *************/

int print_alias(data_of_program *data, char *alias);
char *get_alias(data_of_program *data, char *alias);
int set_alias(char *alias_string, data_of_program *data);

#endif /* SHELL_H */
