/*
** EPITECH PROJECT, 2019
** environment.h minishell
** File description:
** contain the proto and the header of the environment
*/

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

struct env_s {
    char *name;
    char *value;
    struct env_s *next;
};
typedef struct env_s env_t;

env_t **ini_env(char **envp);
char *get_path_commmand(char *command);

#endif /*ENVIRONMENT_H*/
