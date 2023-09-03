#ifndef YK_YEKTOR_H
#define YK_YEKTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct YK_Yektor
{
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} YK_Yektor;

__declspec(dllexport) YK_Yektor *yk_yektor_innit(size_t size, size_t element_size);

__declspec(dllexport) void yk_yektor_push(YK_Yektor *vector, void *element);

__declspec(dllexport) void *yk_yektor_at(YK_Yektor *vector, size_t index);

__declspec(dllexport) void yk_yektor_pop(YK_Yektor *vector);

__declspec(dllexport) void yk_yektor_destroy(YK_Yektor *vector);

__declspec(dllexport) void yk_yektor_print(YK_Yektor *vector);

#endif