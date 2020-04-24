/*
** EPITECH PROJECT, 2020
** check_exit_loop.c
** File description:
** check_exit_loop.c
*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "ftrace.h"

bool check_exit_loop(int status)
{
    if (WIFSIGNALED(status))
        return (false);
    if (WIFSTOPPED(status) && WSTOPSIG(status) != SIGSTOP &&
    WSTOPSIG(status) != SIGTRAP)
        return (false);
    return (true);
}