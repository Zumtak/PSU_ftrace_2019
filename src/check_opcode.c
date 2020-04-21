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


call_type get_calltype(unsigned long opcode)
{
    if (((opcode & 0x0000FFFF) == 0x0000050f)) {
        return SYSCALL;
    }
    if (((opcode & 0xFF) == 0xFF && (opcode & 0x3800) == 0x1000) ||
     ((opcode & 0xFF) == 0xe8)) {
        return CALL;
    }
    if ((opcode & 0xFF) == 0xC2 || (opcode & 0xFF) == 0xC3) {
        return RETN;
    }
    if ((opcode & 0xFF) == 0xCA  || (opcode & 0xFF) == 0xCB) {
        return RETF;
    }
    return NONE;
}