/*
** EPITECH PROJECT, 2020
** display_signal.c
** File description:
** display_signal.c
*/

#include "ftrace.h"
#include "signals.h"
#include <stdio.h>

void display_signals(int signal)
{
    int i = 0;
    int size_tab = 31;

    while (i < size_tab) {
        if (signals_list[i].code == signal) {
            fprintf(stderr, "Received signal %s\n", signals_list->name);
            break;
        }
        i++;
    }
    return;
}