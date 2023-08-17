#include<yk_vector.h>

/*
Vector2f
*/

/*
vec/scalar
*/

YK_Vec2f yk_math_add_vec2f_s(const YK_Vec2f *a, const f4 b)
{
    YK_Vec2f out;
    out.x = a->x + b;
    out.y = a->y + b;
    return out;
}
YK_Vec2f yk_math_sub_vec2f_s(const YK_Vec2f *a, const f4 b)
{
    YK_Vec2f out;
    out.x = a->x - b;
    out.y = a->y - b;
    return out;
}

/*
vec/vec
*/

YK_Vec2f yk_math_add_vec2f(const YK_Vec2f *a, const YK_Vec2f *b)
{
    YK_Vec2f out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    return out;
}

YK_Vec2f yk_math_sub_vec2f(const YK_Vec2f *a, const YK_Vec2f *b)
{
    YK_Vec2f out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    return out;
}

/*
Vector3f
*/

/*
vec/scalar
*/

YK_Vec3f yk_math_add_vec3f_s(const YK_Vec3f *a, const f4 b)
{
    YK_Vec3f out;
    out.x = a->x + b;
    out.y = a->y + b;
    out.z = a->z + b;
    return out;
}
YK_Vec3f yk_math_sub_vec3f_s(const YK_Vec3f *a, const f4 b)
{
    YK_Vec3f out;
    out.x = a->x - b;
    out.y = a->y - b;
    out.z = a->z - b;
    return out;
}

/*
vec/vec
*/

YK_Vec3f yk_math_add_vec3f(const YK_Vec3f *a, const YK_Vec3f *b)
{
    YK_Vec3f out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    out.z = a->z + b->z;
    return out;
}
YK_Vec3f yk_math_sub_vec3f(const YK_Vec3f *a, const YK_Vec3f *b)
{
    YK_Vec3f out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    out.z = a->z - b->z;
    return out;
}
