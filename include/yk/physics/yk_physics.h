#ifndef YK_PHYSICS_H
#define YK_PHYSICS_H
#include <yk/math/yk_math.h>
#include <yk/data_structures/yk_yektor.h>

extern YK_Yektor yk_rigidbodies;

typedef enum YK_Collision_dir
{
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

typedef struct YK_Rigidbody
{
    YK_Vec2f pos;
    YK_Vec2f velocity;
    YK_Vec2f acceleration;
    YK_Vec2f friction;
    f4 mass;
} YK_Rigidbody;

void yk_rigidbody_add(YK_Rigidbody *out);

void yk_rigidbody_innit(YK_Rigidbody *out);
void yk_rigidbody_add_(YK_Vec2f *pos, f4 mass);
YK_Vec2f yk_rigidbody_get_pos(i4 id);
void yk_rigidbody_set_vel(i4 id, YK_Vec2f *vel);
void yk_rigidbody_add_force(i4 id, YK_Vec2f *force);

void yk_physics_innit();

void yk_physics_update(f4 delta);

b1 yk_physics_colliding(YK_Aabb *a, const YK_Aabb *b);

YK_Vec3f yk_physics_get_collision_dir(const YK_Aabb *aabb);

void yk_physics_resolve_collision(YK_Aabb *a, const YK_Aabb *b);

YK_Vec3f yk_physics_get_overlap_distance(YK_Aabb *a, const YK_Aabb *b);



struct YK_AABB
{
    YK_Vec2f min;
    YK_Vec2f max;
};

typedef struct YK_AABB YK_AABB;


b1 yk_physics_aabb_overlap_test(YK_AABB* a, YK_AABB* b);


struct YK_Particle
{
    YK_Vec3f pos;
    
};

typedef struct YK_Particle YK_Particle;

#endif