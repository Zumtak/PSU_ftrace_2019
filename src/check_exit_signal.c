/*
** EPITECH PROJECT, 2020
** check_exit_loop.c
** File description:
** check_exit_loop.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ftrace.h"
#include <signal.h>

bool check_exit_signal(int status)
{
    int	signal = -1;

    if (WSTOPSIG(status) == SIGTRAP || WSTOPSIG(status) == SIGSTOP)
        return (true);
    if (WIFEXITED(status))
        return (false);
    if (WIFSIGNALED(status))
        signal = WTERMSIG(status);
    if (WIFSTOPPED(status))
        signal = WSTOPSIG(status);
    if (signal != -1) {
        display_signals(signal);
        return (false);
    }
    return (true);
}