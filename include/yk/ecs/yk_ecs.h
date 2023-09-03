#ifndef YK_ECS_H
#define YK_ECS_H

#include <yk/data_structures/yk_yektor.h>

extern int total_entities;

__declspec(dllexport) int yk_ecs_create_entity();

__declspec(dllexport) void yk_ecs_gravity_system();



#endif