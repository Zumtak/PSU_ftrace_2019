/*
** EPITECH PROJECT, 2020
** signals.h
** File description:
** signals.h
*/

#ifndef SIGNALS_H
#define SIGNALS_H

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct signame_s
{
    char *name;
    int code;
} t_signame;

t_signame signals_list[] = {
    {"SIGINT", SIGINT},
    {"SIGQUIT", SIGQUIT},
    {"SIGTRAP", SIGTRAP},
    {"SIGILL", SIGILL},
    {"SIGHUP", SIGHUP},
    {"SIGABRT", SIGABRT},
    {"SIGBUS", SIGBUS},
    {"SIGIOT", SIGIOT},
    {"SIGKILL", SIGKILL},
    {"SIGPIPE", SIGPIPE},
    {"SIGFPE", SIGFPE},
    {"SIGALRM", SIGALRM},
    {"SIGUSR1", SIGUSR1},
    {"SIGSEGV", SIGSEGV},
    {"SIGUSR2", SIGUSR2},
    {"SIGCHLD", SIGCHLD},
    {"SIGSTOP", SIGSTOP},
    {"SIGTERM", SIGTERM},
    {"SIGTTIN", SIGTTIN},
    {"SIGTSTP", SIGTSTP},
    {"SIGCONT", SIGCONT},
    {"SIGTTOU", SIGTTOU},
    {"SIGXCPU", SIGXCPU},
    {"SIGXFSZ", SIGXFSZ},
    {"SIGPROF", SIGPROF},
    {"SIGURG", SIGURG},
    {"SIGWINCH", SIGWINCH},
    {"SIGVTALRM", SIGVTALRM},
    {"SIGIO", SIGIO},
    {"SIGSYS", SIGSYS}
};

#endif /* !SIGNALS_H */