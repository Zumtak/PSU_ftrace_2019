/*
** EPITECH PROJECT, 2019
** Ftrace
** File description:
** ftrace main function
*/

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ftrace.h"

char *display_function(pid_t child_pid, struct user_regs_struct regs,
char *file_path, int status)
{
    char *fname = NULL;

    ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL);
    wait(&status);
    ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
    fname = find_symbol(file_path, regs.rip);
    if (fname == NULL)
        fname = dyn_find_symbol(child_pid, regs.rip);
    if (fname == NULL) {
        fname = malloc(sizeof(char) * (21 + strlen(file_path)));
        if (fname == NULL)
            return (NULL);
        sprintf(fname, "func_0x%llx@%s", regs.rip, file_path);
        dprintf(2, "%s\n", fname);
    } else {
        dprintf(2, "Entering function %s at Ox%llx\n", fname, regs.rip);
    }
    return fname;
}

static int tracer_fork(arguments_t *args)
{
    struct user_regs_struct regs = {0};
    int status = 1;

    function_list_t **list = malloc(sizeof(function_list_t *));
    *list = NULL;
    while (!WIFEXITED(status)) {
        ptrace(PTRACE_SINGLESTEP, args->pid, NULL, NULL);
        wait(&status);
        if (!check_exit_loop(status))
            break;
        ptrace(PTRACE_GETREGS, args->pid, 0, &regs);
        process_call(status, args, regs, list);
    }
    status = WEXITSTATUS(status);
    delete_all_list(list);
    dprintf(2, "+++ exited with %d +++\n", status);
    return (status);
}

static int fork_n_trace(arguments_t *args)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
        return (-1);
    if (child_pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        return (execve(args->program_path, args->argv, args->envp));
    }
    args->pid = child_pid;
    return (tracer_fork(args));
}

int ftrace(arguments_t *args)
{
    return (fork_n_trace(args));
}
