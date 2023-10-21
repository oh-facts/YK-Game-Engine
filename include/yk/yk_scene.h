#ifndef YK_SCENE_H
#define YK_SCENE_H
#include <yk/ecs/yk_ecs.h>

typedef struct {
    int* entities;
    size_t num_entities;
} YK_Scene;

void yk_scene_innit(YK_Scene *scene);
void yk_scene_add_entitty(YK_Scene *scene, int id);

#endif