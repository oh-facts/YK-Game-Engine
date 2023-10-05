#include <yk/physics/yk_physics.h>

YK_Yektor particles;

void yk_physics_innit()
{
    yk_yektor_innit(&particles, 5, sizeof(YK_Particle2d));
}

f4 accumulator = 0.f;
#define fixed_delta 0.001f
#define half_a_t2 (fixed_delta*fixed_delta*0.5f)

void yk_particle_integrate(f4 delta)
{
    accumulator += delta;

    while (accumulator > fixed_delta)
    {
        i4 size = particles.size;

        for (i4 i = 0; i < size; i++)
        {
            YK_Particle2d *particle = yk_yektor_get(&particles, i);
            // s = ut + 0.5at^2
            // particle->vel * delta + 0.5f * particle->acc * delta * delta;

            v2f temp = yk_math_vec2f_mul_s(&particle->vel, fixed_delta);
            v2f temp2 = yk_math_vec2f_mul_s(&particle->acc, half_a_t2);
            v2f temp3 = yk_math_vec2f_add(&temp, &temp2);

            particle->pos = yk_math_vec2f_add(&particle->pos, &temp3);

        }

        accumulator -= fixed_delta;
    }
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

YK_Particle2d *yk_particles_create(v2f pos, f4 damping, f4 mass)
{
    return yk_yektor_push(&particles, &(YK_Particle2d){pos, {0, 0}, {0, 0}, damping, 1.f / mass});
}