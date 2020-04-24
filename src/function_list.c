/*
** EPITECH PROJECT, 2020
** PSU_ftrace_2019
** File description:
** function_list
*/

#include <stdlib.h>
#include <stdio.h>
#include "ftrace.h"

void add_function_list(char *function_name, function_list_t **list)
{
    if (list == NULL) {
        return;
    }
    function_list_t *new_function = malloc(sizeof(function_list_t *));
    if (new_function == NULL) {
        return;
    }
    new_function->function = function_name;
    new_function->next = *list;
    *list = new_function;
    return;
}

void display_curr_function_list(function_list_t **list)
{
    printf("\n-----LIST-----\n");
    if (list == NULL) {
        return;
    }
    function_list_t *temp = *list;
    while (temp != NULL) {
        printf("Function in list: %s\n", temp->function);
        temp = temp->next;
    }
    printf("\n----------\n");
}

void pop_function_list(function_list_t **list)
{
    if (list == NULL || *list == NULL) {
        return;
    }
    function_list_t *to_delete = *list;
    *list = to_delete->next;
    free(to_delete->function);
    free(to_delete);
}

void delete_all_list(function_list_t **list)
{
    if (list == NULL || *list == NULL) {
        return;
    }
    function_list_t *temp = *list;
    function_list_t *next = NULL;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

