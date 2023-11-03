#include "shell.h"

/**
 * custom_builtin_env - Display the environment where the shell is running
 * @data: A struct for the program's data
 * Return: Zero on success, or another number if specified in the arguments
 */
int custom_builtin_env(data_of_program *data) {
    int i;
    char var_name[50] = {'\0'};
    char *var_copy = NULL;

    /* Check for arguments */
    if (data->tokens[1] == NULL) {
        custom_print_environment(data);
    } else {
        for (i = 0; data->tokens[1][i]; i++) {
            /* Check if there's a character '=' */
            if (data->tokens[1][i] == '=') {
                var_copy = str_duplicate(custom_env_get_key(var_name, data));
                if (var_copy != NULL)
                    custom_env_set_key(var_name, data->tokens[1] + i + 1, data);

                custom_print_environment(data);

                if (custom_env_get_key(var_name, data) == NULL) {
                    custom_print(data->tokens[1]);
                    custom_print("\n");
                } else {
                    custom_env_set_key(var_name, var_copy, data);
                    free(var_copy);
                }
                return 0;
            }
            var_name[i] = data->tokens[1][i];
        }
        errno = 2;
        perror(data->command_name);
        errno = 127;
    }
    return 0;
}

/**
 * custom_builtin_set_env - ...
 * @data: A struct for the program's data
 * Return: Zero on success, or another number if specified in the arguments
 */
int custom_builtin_set_env(data_of_program *data) {
    /* Validate args */
    if (data->tokens[1] == NULL || data->tokens[2] == NULL)
        return 0;
    if (data->tokens[3] != NULL) {
        errno = E2BIG;
        perror(data->command_name);
        return 5;
    }

    custom_env_set_key(data->tokens[1], data->tokens[2], data);

    return 0;
}

/**
 * custom_builtin_unset_env - ...
 * @data: A struct for the program's data
 * Return: ...
 */
int custom_builtin_unset_env(data_of_program *data) {
    /* Validate args */
    if (data->tokens[1] == NULL)
        return 0;
    if (data->tokens[2] != NULL) {
        errno = E2BIG;
        perror(data->command_name);
        return 5;
    }
    custom_env_remove_key(data->tokens[1], data);
    return 0;
}
