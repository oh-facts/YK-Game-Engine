#ifndef YK_YEKTOR_H
#define YK_YEKTOR_H
#include <stdlib.h>

//Based off of of the kohi engine. I think its better the way he did it instead of using
//structs to define them because meta data is handled in the same cache line as the elements.
//probably not as type safe (I am implementing them myself, I only saw the header file in his
//repo) but if all functionality is encapsulated in functions, then its basically just
//one and done boiler plate type code.

/*
    void pointer type implementation. Encapsulate all functionality to 
    functions to avoid risky type errors.
*/
typedef void* YK_Yektor;

#define YK_YEKTOR_SIZE 0
#define YK_YEKTOR_STRIDE 1
#define YK_YEKTOR_METADATA YK_YEKTOR_STRIDE


YK_Yektor yk_yektor_create(int num_elements,int stride);
void yk_yektor_push(YK_Yektor *arr, void* data);
void yk_yektor_pop(YK_Yektor *yek);




#endif