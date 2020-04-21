/*
** EPITECH PROJECT, 2019
** Ftrace
** File description:
** Dynamique symbols finder
*/

#include <elf.h>
#include <gelf.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "ftrace.h"

static unsigned long long int get_offset_addr(char *line, unsigned long long int addr)
{
    unsigned long long int low_addr = 0;

    line[12] = '\0';
    low_addr = strtol(line, NULL, 16);
    line[12] = '-';
    if (addr > low_addr)
        return (addr - low_addr);
    return (0);
}

static char *search_in_lib(char *line, unsigned long long int addr)
{
    char *func_name = NULL;
    unsigned long long int offset = 0;

    line[strlen(line) - 1] = '\0';
    offset = get_offset_addr(line, addr);
    if (line[73] != '[' && offset != 0)
        func_name = find_symbol(line + 73, offset);
    return (func_name);
}

char *dyn_find_symbol(pid_t pid, unsigned long long int addr)
{
    char *line = NULL;
    char buffer_name[20];
    FILE *maps_file = NULL;
    size_t len = 0;
    char *func_name = NULL;

    if (sprintf(buffer_name, "/proc/%d/maps", pid) == -1)
        return (NULL);
    maps_file = fopen(buffer_name, "r");
    if (maps_file == NULL)
        return (NULL);
    while (getline(&line, &len, maps_file) != -1) {
        func_name = search_in_lib(line, addr);
        if (func_name != NULL)
            break;
    }
    fclose(maps_file);
    return (func_name);
}
