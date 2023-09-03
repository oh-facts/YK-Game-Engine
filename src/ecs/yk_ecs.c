#include <yk/ecs/yk_ecs.h>

int total_entities = 0;


int yk_ecs_create_entity()
{
    return total_entities++;
}