#ifndef YK_PHYSICS_H
#define YK_PHYSICS_H
#include "yk/rendering/yk_renderer2d.h"
#include <yk/math/yk_math.h>
#include <yk/data_structures/yk_yektor.h>

enum YK_COLLISION_SHAPE
{
  YK_COLLISION_SHAPE_NONE,
  YK_COLLISION_SHAPE_RECT,
  YK_COLLISION_SHAPE_CIRCLE
};


struct YK_AABB
{
  v2f min;
  v2f max;
};

typedef struct YK_AABB YK_AABB;

struct YK_Circle
{
  v2f center;
  f4 radius;
};

typedef struct YK_Circle YK_Circle;


struct YK_Collider
{
  union
  {
    YK_Circle circle;
    YK_AABB aabb;

  } collision_shape;

  v2f offset;

};

typedef struct YK_Collider YK_Collider;

b1 yk_physics_aabb_overlap_test(YK_AABB *a, YK_AABB *b);

struct YK_Particle2d
{
  v2f pos;
  v2f vel;
  v2f acc;
  f4 damping;
  f4 i_mass;
  i4 collision_shape_type;
  YK_Collider collider;
};

typedef struct YK_Particle2d YK_Particle2d;

void yk_physics_innit();
void yk_particle_integrate(f4 delta);
void yk_particle_set_aabb(YK_Particle2d *out, v2f pos, v2f scale);
YK_AABB yk_particle_create_aabb(v2f pos, v2f scale);
b1 yk_particle_collision_test(YK_Particle2d *a, YK_Particle2d *b);
void yk_particle_collision_shape_update(YK_Particle2d *particle);
void yk_particle_collison_shape_debug_draw(YK_Renderer2d *ren);
void yk_aabb_update_pos(YK_AABB *out, v2f pos);

v2f yk_aabb_get_pos(YK_AABB *aabb);

v2f yk_aabb_get_scale(YK_AABB *aabb);

YK_Particle2d *yk_particles_create(v2f pos, f4 damping, f4 mass);

#endif
