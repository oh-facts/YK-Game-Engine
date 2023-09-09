#include <yk/physics/yk_physics.h>

b1 yk_physics_colliding(const YK_Aabb *a, const YK_Aabb *b)
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

   f4 minOverlapX = halfWidthA + halfWidthB;
   f4 minOverlapY = halfHeightA + halfHeightB;

    if (fabsf(deltaX) < minOverlapX && fabsf(deltaY) < minOverlapY)
    {
        return true;
    }

    return false;
}
