#ifndef YK_PHYSICS_H
#define YK_PHYSICS_H
#include <yk/math/yk_math.h>

typedef struct YK_Aabb
{
    YK_Vec2f pos;
    YK_Vec2f size;

} YK_Aabb;

b1 yk_physics_colliding(const YK_Aabb *a, const YK_Aabb *b);

#endif