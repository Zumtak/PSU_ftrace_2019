/*
** EPITECH PROJECT, 2020
** process_call.c
** File description:
** process_call
*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "ftrace.h"

void process_call(int status, arguments_t *args, struct user_regs_struct regs,
function_list_t **list)
{
    unsigned long opcode = ptrace(PTRACE_PEEKTEXT, args->pid, regs.rip,
    regs);
    call_type_t call_type = get_calltype(opcode);

    if (call_type == CALL) {
        char *function_name = display_function(args->pid, regs,
        args->program_path,
        status);
        add_function_list(function_name, list);
    } else if (call_type == RET && *list != NULL) {
        dprintf(2, "Leaving function %s\n", (*list)->function);
        pop_function_list(list);
    }
    if (regs.orig_rax != -1) {
        display(regs, args->pid);
    }
}