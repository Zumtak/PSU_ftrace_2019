/*
** EPITECH PROJECT, 2019
** Ftrace
** File description:
** ftrace main function
*/

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ftrace.h"

# define SYSCALL(opcode)        ((opcode & 0x0000FFFF) == 0x0000050f)
# define RELCALL(opcode)	((opcode & 0xFF) == 0xe8)
# define INDCALL(o)		((o & 0xFF) == 0xFF && (o & 0x3800) == 0x1000)
# define CALL(op)		(SYSCALL(op) || RELCALL(op) || INDCALL(op))
# define R_1(op)		((op & 0xFF) == 0xC3 || (op & 0xFF) == 0xC2)
# define R_2(op)		((op & 0xFF) == 0xCA  || (op & 0xFF) == 0xCB)
# define RET(op)		(R_1(op) || R_2(op))

static int tracer_fork(pid_t child_pid)
{
    struct user_regs_struct regs = {0};
    int status = 1;

    while (!WIFEXITED(status)) {
        ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL);
        wait(&status);
        if (WIFSIGNALED(status))
            break;
        if (WIFSTOPPED(status) && WSTOPSIG(status) != SIGSTOP &&
        WSTOPSIG(status) != SIGTRAP)
            break;
        ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
        unsigned long long int opcode = ptrace(PTRACE_PEEKTEXT, child_pid, regs.rip, regs);
        if (SYSCALL(opcode)) {
            printf("SYSCALL Detected\n");
        }
        if (CALL(opcode)) {
            printf("CALL Detected\n");
        }
        if (RELCALL(opcode)) {
            printf("RELCALL Detectec\n");
            get_addr_relative(child_pid, regs);
        }
        if (INDCALL(opcode)) {
            printf("INDCALL Detected\n");
        }
        if (regs.orig_rax != -1)
            display(regs, child_pid);
    }
    status = WEXITSTATUS(status);
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
    return (tracer_fork(child_pid));
}

int ftrace(arguments_t *args)
{
    return (fork_n_trace(args));
}
