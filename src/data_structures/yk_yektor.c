#include <yk/data_structures/yk_yektor.h>

YK_Yektor *yk_yektor_innit(size_t size, size_t element_size)
{
    YK_Yektor *vector = (YK_Yektor *)malloc(sizeof(YK_Yektor));
    if (vector == NULL)
    {
        perror("YK_Yektor initialization failed");
        exit(EXIT_FAILURE);
    }

    vector->data = malloc(size * element_size);
    if (vector->data == NULL)
    {
        perror("YK_Yektor data allocation failed");
        free(vector);
        exit(EXIT_FAILURE);
    }

    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = size;

    return vector;
}

void yk_yektor_push(YK_Yektor *vector, void *element)
{
    if (vector->size == vector->capacity)
    {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, vector->capacity * vector->element_size);
        if (vector->data == NULL)
        {
            perror("YK_Yektor resizing failed");
            exit(EXIT_FAILURE);
        }
    }

    void *dest = (char *)vector->data + (vector->size * vector->element_size);
    memcpy(dest, element, vector->element_size);
    vector->size++;
}

void *yk_yektor_at(YK_Yektor *vector, size_t index)
{
    if (index < vector->size)
    {
        return (char *)vector->data + (index * vector->element_size);
    }
    else
    {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }
}

void yk_yektor_pop(YK_Yektor *vector)
{
    if (vector->size > 0)
    {
        vector->size--;
    }
}

void yk_yektor_destroy(YK_Yektor *vector)
{
    free(vector->data);
    free(vector);
}

void yk_yektor_print(YK_Yektor *vector)
{
    if (vector == NULL)
    {
        printf("Yektor is NULL\n");
        return;
    }

    printf("Yektor Size: %zu\n", vector->size);
    printf("Yektor Capacity: %zu\n", vector->capacity);
    printf("Yektor Element Size: %zu\n", vector->element_size);

    printf("Yektor Contents:\n");

    if (vector->data == NULL)
    {
        printf("Yektor is empty\n");
        return;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        void *element = yk_yektor_at(vector, i);
        printf("[%zu]: %p\n", i, element);
    }
}