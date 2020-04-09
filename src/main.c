/*
** EPITECH PROJECT, 2020
** PSU_ftrace_2019
** File description:
** main
*/

#include <stdlib.h>
#include <string.h>
#include "ftrace.h"

static void free_struct(arguments_t *args)
{
    free(args->argv);
    free(args->program_path);
    free(args);
}

int main(int argc, char *argv[], char **envp)
{
    int res_ftrace = 0;
    arguments_t *args = manage_arguments(argc, argv, envp);

    if (args == NULL) {
        return 84;
    }
    res_ftrace = ftrace(args);
    free_struct(args);
    return (res_ftrace);
}
