#ifndef YK_PHYSICS_H
#define YK_PHYSICS_H
#include <yk/math/yk_math.h>
#include <yk/data_structures/yk_yektor.h>


struct YK_AABB
{
    v2f min;
    v2f max;
};

typedef struct YK_AABB YK_AABB;


b1 yk_physics_aabb_overlap_test(YK_AABB* a, YK_AABB* b);

//To do: Make 2d versions of everything to preserve sanity.

struct YK_Particle
{
    v3f pos;
    v3f vel;
    v3f acc;
    f4 damping;
    f4 i_mass;
    
};

typedef struct YK_Particle YK_Particle;

void yk_particle_integrate(YK_Particle *self, f4 time_step);

#endif