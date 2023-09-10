#ifndef YK_PHYSICS_H
#define YK_PHYSICS_H
#include <yk/math/yk_math.h>

typedef enum YK_Collision_dir {
    COLLISION_NONE,
    COLLISION_LEFT,
    COLLISION_RIGHT,
    COLLISION_TOP,
    COLLISION_BOTTOM,
} YK_Collision_dir;


typedef struct YK_Aabb
{
    YK_Vec2f pos;
    YK_Vec2f size;
    YK_Collision_dir coll_dir;

} YK_Aabb;

b1 yk_physics_colliding(YK_Aabb *a, const YK_Aabb *b);

YK_Vec3f yk_physics_get_collision_dir(const YK_Aabb* aabb);

#endif