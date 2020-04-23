/*
** EPITECH PROJECT, 2019
** ftrace
** File description:
** Display syscall functions
*/

#include <stdio.h>
#include <stddef.h>
#include <sys/user.h>
#include "ftrace.h"
#include "syscall_list.h"

const system_function_t *get_instruction(int syscall)
{
    int i = 0;

    while (i < 333) {
        if (sys_function[i].define_id == syscall)
            return (&sys_function[i]);
        ++i;
    }
    return (NULL);
}

void display(struct user_regs_struct regs, pid_t pid)
{
    int i = 0;
    const system_function_t *tmp = get_instruction(regs.orig_rax);
    const unsigned long long reg_tab[6] = {regs.rdi, regs.rsi, regs.rdx,
    regs.rcx, regs.r8, regs.r9};

    (void)pid;
    if (tmp == NULL)
        return;
    dprintf(2, "Syscall %s(", tmp->name);
    while (i < tmp->nb_arguments - 1) {
        dprintf(2, "0x%llx, ", reg_tab[i]);
        ++i;
    }
    dprintf(2, "0x%llx) = 0x%llx\n", reg_tab[i], regs.rax);
}