#include <yk/yk_scene.h>

void yk_scene_innit(YK_Scene *scene)
{
    scene->entities = NULL;
    scene->num_entities = 0;
}
void yk_scene_add_entitty(YK_Scene *scene, int id)
{
    scene->num_entities++;

    scene->entities = (int *)realloc(scene->entities, sizeof(int) * scene->num_entities);

    if (scene->entities == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    scene->entities[scene->num_entities - 1] = id;
}