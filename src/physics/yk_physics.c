#include <yk/physics/yk_physics.h>

YK_Yektor particles;

void yk_physics_innit()
{
    yk_yektor_innit(&particles, 5, sizeof(YK_Particle2d));
}

void yk_particle_integrate(f4 duration)
{
    
}

b1 yk_physics_aabb_overlap_test(YK_AABB *a, YK_AABB *b)
{
    f4 d1x = b->min.x - a->max.x;
    f4 d1y = b->min.y - a->max.y;
    f4 d2x = a->min.x - b->max.x;
    f4 d2y = a->min.y - b->max.y;

    if (d1x > 0.0f || d1y > 0.0f)
        return false;

    if (d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}
