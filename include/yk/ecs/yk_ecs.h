#ifndef YK_ECS_H
#define YK_ECS_H

/*
  To Do
    1. Make Vectors
    2. Make ecs
    3. make physics
    4. make api
    5. clean up engine
    6. make mario-hiemer
*/

int total_entities = 0;

int yk_ecs_create_entity()
{
    return total_entities++;
}

typedef struct YK_Position_component
{
    float x,y;
}YK_Position_component;

YK_Position_component pos_comps[10];

void yk_ecs_add_position_component(int id)
{
    YK_Position_component comp;
    comp.x = 0;
    comp.y = 0;
    pos_comps[id] = comp;
}

void yk_ecs_gravity_system()
{
    for(int i = 0 ; i < 10; i ++)
    {
        pos_comps[i].y--;
    }
}


#endif