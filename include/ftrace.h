/*
** EPITECH PROJECT, 2020
** PSU_ftrace_2019
** File description:
** ftrace
*/

#ifndef ftrace_H_
#define ftrace_H_

#include <sys/user.h>
#include <unistd.h>
#include "environment.h"

enum type_e { UNDEFINED = 0, INT = 1, STR = 2, PTR = 3 };

struct arguments_s {
    pid_t pid;
    char *program_path;
    char *program_name;
    int argc;
    char **argv;
    char *const *envp;
};
typedef struct arguments_s arguments_t;

struct system_function_s {
    int define_id;
    enum type_e return_value;
    char *name;
    enum type_e arguments[6];
    int nb_arguments;
};
typedef struct system_function_s system_function_t;

enum call_type {
    NONE = 0,
    SYSCALL = 1,
    CALL = 2,
    RETN = 3,
    RETF = 4
};
typedef enum call_type call_type;

arguments_t* initialize_arguments();
void display_arguments_struct(arguments_t* arguments);
arguments_t *manage_arguments(int argc, char **argv, char **envp);

void display(struct user_regs_struct regs, pid_t pid);
void display_str(struct user_regs_struct regs, pid_t pid);

int ftrace(arguments_t *args);

call_type get_calltype(unsigned long opcode);

const system_function_t *get_instruction(int syscall);
#endif /* !ftrace_H_ */
