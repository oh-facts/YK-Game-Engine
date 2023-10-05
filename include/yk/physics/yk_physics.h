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


struct YK_Particle2d
{
    v2f pos;
    v2f vel;
    v2f acc;
    f4 damping;
    f4 i_mass;
    
};

typedef struct YK_Particle2d YK_Particle2d;

void yk_physics_innit();
void yk_particle_integrate(f4 delta);
YK_Particle2d* yk_particles_create(v2f pos, f4 damping, f4 mass);


#endif