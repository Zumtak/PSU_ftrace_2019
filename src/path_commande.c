/*
** EPITECH PROJECT, 2019
** path_commande.c minishell
** File description:
** manage the command from the path
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "environment.h"
#include "lib.h"

static char *my_strcat(char *str1, char *str2)
{
    char *result = malloc(strlen(str1) + strlen(str2) + 2);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return (NULL);
    }
    strcpy(result, str1);
    result[strlen(str1)] = '/';
    result[strlen(str1) + 1] = 0;
    strcat(result + 1, str2);
    return result;
}

char *get_path_commmand(char *command)
{
    char *path_var = strdup(getenv("PATH"));
    char *tmp = strtok(path_var, ":");
    char *tmp_cmd = NULL;

    while (tmp != NULL) {
        tmp_cmd = my_strcat(tmp, command);
        if (access(tmp_cmd, F_OK) == 0) {
            free(path_var);
            return (tmp_cmd);
        }
        free(tmp_cmd);
        tmp = strtok(NULL, ":");
    }
    free(path_var);
    return (NULL);
}

