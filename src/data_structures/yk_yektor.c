#include <yk/data_structures/yk_yektor.h>

YK_Yektor yk_yektor_create(int num_elements, int stride)
{
    int *out = (int *)malloc(YK_YEKTOR_METADATA * sizeof(int) + num_elements * stride);
    out[YK_YEKTOR_SIZE] = num_elements;
    out[YK_YEKTOR_STRIDE] = stride;

    return (YK_Yektor)out;
}

void yk_yektor_push(YK_Yektor *yek, void *data)
{
   
}

void yk_yektor_pop(YK_Yektor *yek)
{
}