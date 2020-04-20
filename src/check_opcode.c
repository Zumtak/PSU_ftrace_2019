/*
** EPITECH PROJECT, 2020
** PSU_ftrace_2019
** File description:
** check_opcode
*/

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ftrace.h"

unsigned long long int  addr_relative(unsigned long long int opcode, char rexw, pid_t child,  struct user_regs_struct regs)
{
    int offset = 0;
    unsigned long long int  address = 0;

    offset = (int)((opcode >> 8));
    offset = ptrace(PTRACE_PEEKTEXT, child, regs.rip + 1);
    return regs.rip + offset + 9;
}

unsigned long long int get_addr_relative(pid_t child, struct user_regs_struct regs)
{
    unsigned long long int opcode = ptrace(PTRACE_PEEKTEXT, child, regs.rip, regs.rip);
    char rex = 0;
    unsigned long long int addr = addr_relative(opcode, rex, child, regs);
    printf("addr: 0x%llx\n", addr);
    return addr;
}