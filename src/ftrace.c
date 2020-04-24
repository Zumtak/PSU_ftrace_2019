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
        sprintf(fname, "func_0x%llx@%s", regs.rip, file_path);
        dprintf(2, "%s\n", fname);
    } else {
        dprintf(2, "Entering function %s at Ox%llx\n", fname, regs.rip);
    }
    return fname;
}

static int tracer_fork(pid_t child_pid, char *file_path)
{
    struct user_regs_struct regs = {0};
    int status = 1;

    function_list_t **list = malloc(sizeof(function_list_t *));
    *list = NULL;
    while (!WIFEXITED(status)) {
        ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL);
        wait(&status);
        if (WIFSIGNALED(status))
            break;
        if (WIFSTOPPED(status) && WSTOPSIG(status) != SIGSTOP &&
        WSTOPSIG(status) != SIGTRAP)
            break;
        ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
        unsigned long opcode = ptrace(PTRACE_PEEKTEXT, child_pid, regs.rip,
        regs);
        call_type_t call_type = get_calltype(opcode);
        if (call_type == CALL) {
            char *function_name = display_function(child_pid, regs, file_path, status);
            add_function_list(function_name, list);
        } else if (call_type == RET && *list != NULL) {
            dprintf(2, "Leaving function %s\n", (*list)->function);
            pop_function_list(list);
        }
        if (regs.orig_rax != -1) {
            display(regs, child_pid);
        }
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
    return (tracer_fork(child_pid, args->program_path));
}

int ftrace(arguments_t *args)
{
    return (fork_n_trace(args));
}
