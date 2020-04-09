/*
** EPITECH PROJECT, 2019
** ftrace
** File description:
** free double array
*/

#include <stdlib.h>

void free_d_array(void **array)
{
    int i = 0;

    if (array == NULL)
        return;
    while (array[i]) {
        free(array[i]);
        ++i;
    }
    free(array);
}
