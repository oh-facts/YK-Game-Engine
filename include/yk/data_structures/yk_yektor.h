#ifndef YK_YEKTOR_H
#define YK_YEKTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Resizable.
    When you push to a yektor, the yektor creates a copy and is
    meant to own it. When pushing, it returns a ptr to it, incase
    you want to edit it.

    size: current number of elements

    capacity: number of elements allocated

    size <=capacity
    Must be freed with yk_yektor_destroy.
    But only if you want to free it.
    It is your choice. And your choice only.
*/
typedef struct YK_Yektor
{
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} YK_Yektor;


void yk_yektor_innit(YK_Yektor *vector, size_t capacity, size_t element_size);

void *yk_yektor_push(YK_Yektor *vector, void *element);

void yk_yektor_insert(YK_Yektor *vector, void *element, size_t index);

void yk_yektor_set(YK_Yektor *vector, void *element, size_t index);

/*
Returns a pointer to the data.
*/
void *yk_yektor_get(YK_Yektor *vector, size_t index);

void yk_yektor_pop(YK_Yektor *vector);

void yk_yektor_destroy(YK_Yektor *vector);

void yk_yektor_print(YK_Yektor *vector);

#endif