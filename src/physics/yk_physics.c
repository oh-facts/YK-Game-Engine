#include <yk/physics/yk_physics.h>

YK_Yektor yk_rigidbodies;

void yk_rigidbody_innit(YK_Rigidbody *out)
{
    out->acceleration.x = 0;
    out->acceleration.y = 0;

    out->velocity.x = 0;
    out->velocity.y = 0;

    out->mass = 0;
    out->pos.x = 0;
    out->pos.y = 0;
}

void yk_rigidbody_add(YK_Rigidbody *out)
{
    yk_yektor_push(&yk_rigidbodies, out);
}

void yk_physics_innit()
{
    yk_yektor_innit(&yk_rigidbodies, 1, sizeof(YK_Rigidbody));
}

// I really really don't know if its better like this or to copy values.
void yk_rigidbody_add_(YK_Vec2f *pos, f4 mass)
{
    yk_yektor_push(&yk_rigidbodies, &(YK_Rigidbody){*pos, {0, 0}, {0, 0}, mass});
}

f4 accumulator = 0.f;
#define fixed_delta 0.001f

void yk_physics_update(f4 delta)
{
    accumulator += delta;

    while (accumulator > fixed_delta)
    {

        for (i4 i = 0; i < yk_rigidbodies.size; i++)
        {
            YK_Rigidbody *current = yk_yektor_get(&yk_rigidbodies, i);

            YK_Vec2f _at = yk_math_vec2f_mul_s(&current->acceleration, fixed_delta);

            current->velocity = yk_math_vec2f_add(&current->velocity, &_at);

            YK_Vec2f _temp_v = yk_math_vec2f_mul_s(&current->velocity, fixed_delta);
            current->pos = yk_math_vec2f_add(&current->pos, &_temp_v);

            // printf("%f \n",current->pos.x);
        }
        accumulator -= fixed_delta;
    }
}

YK_Vec2f yk_rigidbody_get_pos(i4 id)
{
    return ((YK_Rigidbody *)yk_yektor_get(&yk_rigidbodies, id))->pos;
}

void yk_rigidbody_set_vel(i4 id, YK_Vec2f *vel)
{
    ((YK_Rigidbody *)yk_yektor_get(&yk_rigidbodies, id))->velocity = *vel;
}

void yk_rigidbody_add_force(i4 id, YK_Vec2f *force)
{
    YK_Vec2f *_acc = &((YK_Rigidbody *)yk_yektor_get(&yk_rigidbodies, id))->acceleration;
    *_acc = yk_math_vec2f_add(_acc, force);
}

b1 yk_physics_colliding(YK_Aabb *a, const YK_Aabb *b)
{
    f4 halfWidthA = a->size.x / 2.0f;
    f4 halfHeightA = a->size.y / 2.0f;
    f4 halfWidthB = b->size.x / 2.0f;
    f4 halfHeightB = b->size.y / 2.0f;

    f4 centerXA = a->pos.x;
    f4 centerYA = a->pos.y;
    f4 centerXB = b->pos.x;
    f4 centerYB = b->pos.y;

    f4 deltaX = centerXB - centerXA;
    f4 deltaY = centerYB - centerYA;

    f4 overlapX = halfWidthA + halfWidthB - fabsf(deltaX);
    f4 overlapY = halfHeightA + halfHeightB - fabsf(deltaY);

    if (overlapX > 0 && overlapY > 0)
    {
        if (overlapX < overlapY)
        {
            if (deltaX > 0)
            {
                a->coll_dir = COLLISION_LEFT;
            }
            else
            {
                a->coll_dir = COLLISION_RIGHT;
            }
        }
        else
        {
            if (deltaY > 0)
            {
                a->coll_dir = COLLISION_TOP;
            }
            else
            {
                a->coll_dir = COLLISION_BOTTOM;
            }
        }

        return true;
    }

    a->coll_dir = COLLISION_NONE;
    return false;
}

YK_Vec3f yk_physics_get_collision_dir(const YK_Aabb *aabb)
{
    YK_Vec3f out_coll_dir = {0.0f, 0.0f, 0.f};

    switch (aabb->coll_dir)
    {
    case COLLISION_LEFT:
        out_coll_dir.x = -1.0f;
        break;
    case COLLISION_RIGHT:
        out_coll_dir.x = 1.0f;
        break;
    case COLLISION_TOP:
        out_coll_dir.y = -1.0f;
        break;
    case COLLISION_BOTTOM:
        out_coll_dir.y = 1.0f;
        break;
    case COLLISION_NONE:
        out_coll_dir.x = 0.f;
        out_coll_dir.y = 0.f;

    default:

        break;
    }

    return out_coll_dir;
}

void yk_physics_resolve_collision(YK_Aabb *a, const YK_Aabb *b)
{
    f4 halfWidthA = a->size.x / 2.0f;
    f4 halfHeightA = a->size.y / 2.0f;
    f4 halfWidthB = b->size.x / 2.0f;
    f4 halfHeightB = b->size.y / 2.0f;

    f4 centerXA = a->pos.x;
    f4 centerYA = a->pos.y;
    f4 centerXB = b->pos.x;
    f4 centerYB = b->pos.y;

    f4 deltaX = centerXB - centerXA;
    f4 deltaY = centerYB - centerYA;

    f4 overlapX = halfWidthA + halfWidthB - fabsf(deltaX);
    f4 overlapY = halfHeightA + halfHeightB - fabsf(deltaY);

    if (overlapX > 0 && overlapY > 0)
    {
        if (overlapX < overlapY)
        {
            if (deltaX > 0)
            {
                a->pos.x += overlapX;
            }
            else
            {
                a->pos.x -= overlapX;
            }
        }
        else
        {
            if (deltaY > 0)
            {
                a->pos.y += overlapY;
            }
            else
            {
                a->pos.y -= overlapY;
            }
        }
    }

    if (overlapX < overlapY)
    {
        if (deltaX > 0)
        {
            a->coll_dir = COLLISION_LEFT;
        }
        else
        {
            a->coll_dir = COLLISION_RIGHT;
        }
    }
    else
    {
        if (deltaY > 0)
        {
            a->coll_dir = COLLISION_TOP;
        }
        else
        {
            a->coll_dir = COLLISION_BOTTOM;
        }
    }
}

YK_Vec3f yk_physics_get_overlap_distance(YK_Aabb *a, const YK_Aabb *b)
{
    YK_Vec3f translation = {0.0f, 0.0f, 0.0f};

    f4 halfWidthA = a->size.x / 2.0f;
    f4 halfHeightA = a->size.y / 2.0f;
    f4 halfWidthB = b->size.x / 2.0f;
    f4 halfHeightB = b->size.y / 2.0f;

    f4 centerXA = a->pos.x;
    f4 centerYA = a->pos.y;
    f4 centerXB = b->pos.x;
    f4 centerYB = b->pos.y;

    f4 deltaX = centerXB - centerXA;
    f4 deltaY = centerYB - centerYA;

    f4 overlapX = halfWidthA + halfWidthB - fabsf(deltaX);
    f4 overlapY = halfHeightA + halfHeightB - fabsf(deltaY);

    if (overlapX > 0 && overlapY > 0)
    {
        if (overlapX < overlapY)
        {
            if (deltaX > 0)
            {
                translation.x = overlapX;
                a->coll_dir = COLLISION_LEFT;
            }
            else
            {
                translation.x = -overlapX;
                a->coll_dir = COLLISION_RIGHT;
            }
        }
        else
        {
            if (deltaY > 0)
            {
                translation.y = overlapY;
                a->coll_dir = COLLISION_TOP;
            }
            else
            {
                translation.y = -overlapY;
                a->coll_dir = COLLISION_BOTTOM;
            }
        }
    }
    else
    {
        a->coll_dir = COLLISION_NONE;
    }

    return translation;
}
