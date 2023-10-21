#ifndef YK_PHYSICS_H
#define YK_PHYSICS_H
#include "yk/rendering/yk_renderer2d.h"
#include <yk/math/yk_math.h>
#include <yk/data_structures/yk_yektor.h>

/*
  collision shape ids
*/
enum YK_COLLISION_SHAPE
{
  YK_COLLISION_SHAPE_NONE,
  YK_COLLISION_SHAPE_RECT,
  YK_COLLISION_SHAPE_CIRCLE
};

/*
  aabb collision shape
*/
typedef struct YK_AABB
{
  v2f min;
  v2f max;
} YK_AABB;

/*
  circle collision shape
*/
typedef struct YK_Circle
{
  v2f center;
  f4 radius;
} YK_Circle;

/*
  Physics Collider 
*/
typedef struct YK_Collider
{
  union
  {
    YK_Circle circle;
    YK_AABB aabb;

  } collision_shape;

  v2f offset;

} YK_Collider;

/*
  Tests aabb/aabb collision
*/
b1 yk_physics_aabb_overlap_test(YK_AABB *a, YK_AABB *b);


/*
  A physics particle. Won't be added to simulation if instantiated
  normally. Needs to be created using yk_particle_create
*/
typedef struct YK_Particle2d
{
  v2f pos;
  v2f vel;
  v2f acc;
  f4 damping;
  f4 i_mass;
  i4 collision_shape_type;
  YK_Collider collider;
  b1 debug_draw;
} YK_Particle2d;

/*
  Initializes the physics sim
*/
void yk_physics_innit();

/*
  sets particle aabb
*/
void yk_particle_set_aabb(YK_Particle2d *out, v2f pos, v2f scale);

/*
  Creates an AABB with pos and scale
*/
YK_AABB yk_particle_create_aabb(v2f pos, v2f scale);

/*
  physics update. needs to be called every frame
*/
void yk_particle_integrate(f4 delta);


/*

*/
void yk_particle_overlap_resolve(YK_Particle2d* a, YK_Particle2d* b);

/*
  Draw particle collision shapes, but only for particles that have debug shape drawing
  enabled
*/
void yk_particle_collison_shape_debug_draw(YK_Renderer2d *ren);

/*
  calculates position of aabb
*/
v2f yk_aabb_get_pos(YK_AABB *aabb);

/*
  calculates scale of aabb
*/
v2f yk_aabb_get_scale(YK_AABB *aabb);

/*
  creates a particle and adds it to the physics sim.
  Returns a handle to the particle.
  Particle is owned by the sim.
*/
YK_Particle2d *yk_particles_create(v2f pos, f4 damping, f4 mass);


#endif
