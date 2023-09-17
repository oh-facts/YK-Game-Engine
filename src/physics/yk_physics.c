#include <yk/physics/yk_physics.h>

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