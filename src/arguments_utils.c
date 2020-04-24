/*
** EPITECH PROJECT, 2020
** PSU_ftrace_2019
** File description:
** arguments_utils
*/

#include <stdlib.h>
#include <stdio.h>
#include "ftrace.h"

arguments_t *initialize_arguments(char **env)
{
    arguments_t *arguments = malloc(sizeof(arguments_t));
    if (arguments == NULL) {
        return NULL;
    }
    arguments->program_path = 0;
    arguments->program_name = NULL;
    arguments->program_path = NULL;
    arguments->argc = 0;
    arguments->argv = NULL;
    arguments->envp = env;
    return arguments;
}

void display_arguments_struct(arguments_t *arguments)
{
    int idx = 0;

    if (arguments == NULL) {
        return;
    }
    if (arguments->program_path != NULL)
        printf("program_path: %s\n", arguments->program_path);
    if (arguments->program_name != NULL)
        printf("program_name: %s\n", arguments->program_name);
    printf("argc: %d\n", arguments->argc);
    while (idx != arguments->argc) {
        printf("arg[%d]: %s\n", idx, arguments->argv[idx]);
        ++idx;
    }
}