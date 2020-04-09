/*
** EPITECH PROJECT, 2020
** PSU_ftrace_2019
** File description:
** manage_arguments
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "ftrace.h"

static int get_program_name(char *command, arguments_t *arguments)
{
    char *path_command = NULL;

    if (strlen(command) > 2 && command[0] == '.' && command[1] == '/') {
        arguments->program_name = command;
        arguments->program_path = strdup(command);
        return 1;
    }
    path_command = get_path_commmand(command);
    if (path_command != NULL) {
        arguments->program_name = command;
        arguments->program_path = path_command;
        return 1;
    }
    return 0;
}

static int get_arguments(int argc, char **argv, int idx, arguments_t *arguments)
{
    int comm_argc = argc - idx;
    char **comm_argv = malloc(sizeof(char *) * (comm_argc + 1));
    int idx_comm = 1;
    if (comm_argv == NULL) {
        return 0;
    }
    arguments->argc = comm_argc;
    comm_argv[0] = arguments->program_path;
    while (++idx != argc) {
        comm_argv[idx_comm] = argv[idx];
        ++idx_comm;
    }
    comm_argv[idx_comm] = NULL;
    arguments->argv = comm_argv;
    return 1;
}

arguments_t *manage_arguments(int argc, char **argv, char **envp)
{
    int idx = 1;
    arguments_t *arguments = initialize_arguments(envp);

    if (argc == 1) {
        if (arguments != NULL)
            free(arguments);
        return NULL;
    }
    if (!get_program_name(argv[idx], arguments)
        || !get_arguments(argc, argv, idx, arguments)) {
        free(arguments);
        return NULL;
    }
    return arguments;
}
