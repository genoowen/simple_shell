#include "shell.h"

/**
 * custom_builtins_list - search for a match and execute the associated builtin
 * @data: struct for the program's data
 * Return: Returns the return of the executed function if there is a match,
 * otherwise returns -1.
 **/
int custom_builtins_list(data_of_program *data)
{
    int iterator;
    builtins options[] = {
        {"exit", custom_builtin_exit},
        {"help", custom_builtin_help},
        {"cd", custom_builtin_cd},
        {"alias", custom_builtin_alias},
        {"env", custom_builtin_env},
        {"setenv", custom_builtin_set_env},
        {"unsetenv", custom_builtin_unset_env},
        {NULL, NULL}
    };

    /* Walk through the structure */
    for (iterator = 0; options[iterator].builtin != NULL; iterator++)
    {
        /* If there is a match between the given command and a builtin, */
        if (str_compare(options[iterator].builtin, data->command_name, 0))
        {
            /* Execute the function and return the return value of the function */
            return (options[iterator].function(data));
        }
    }
    /* If there is no match, return -1 */
    return (-1);
}
