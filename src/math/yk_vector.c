#include <yk/math/yk_vector.h>

/*
Vector2f
*/
f4 yk_vec2f_length(const YK_Vec2f *a)
{
    f4 out;
    out = sqrtf((a->x) * (a->x) + (a->y) * (a->y));

    return out;
}

YK_Vec2f yk_vec2f_normalize(const YK_Vec2f *a)
{
    YK_Vec2f out;
    out = yk_math_vec2f_div_s(a, yk_vec2f_length(a));

    return out;
}

void yk_vec2f_print(const YK_Vec2f *a)
{
    printf("x: %f y: %f\n", a->x, a->y);
}

/*
vec/scalar
*/

YK_Vec2f yk_math_vec2f_add_s(const YK_Vec2f *a, const f4 b)
{
    YK_Vec2f out;
    out.x = a->x + b;
    out.y = a->y + b;
    return out;
}
YK_Vec2f yk_math_vec2f_sub_s(const YK_Vec2f *a, const f4 b)
{
    YK_Vec2f out;
    out.x = a->x - b;
    out.y = a->y - b;
    return out;
}
YK_Vec2f yk_math_vec2f_mul_s(const YK_Vec2f *a, const f4 b)
{
    YK_Vec2f out;
    out.x = a->x * b;
    out.y = a->y * b;
    return out;
}
YK_Vec2f yk_math_vec2f_div_s(const YK_Vec2f *a, const f4 b)
{
    YK_Vec2f out;
    out.x = a->x / b;
    out.y = a->y / b;
    return out;
}
/*
vec/vec
*/

YK_Vec2f yk_math_vec2f_add(const YK_Vec2f *a, const YK_Vec2f *b)
{
    YK_Vec2f out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    return out;
}

YK_Vec2f yk_math_vec2f_sub(const YK_Vec2f *a, const YK_Vec2f *b)
{
    YK_Vec2f out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    return out;
}

/*
Vector3f
*/

f4 yk_vec3f_length(const YK_Vec3f *a)
{
    f4 out;
    out = sqrtf((a->x) * (a->x) + (a->y) * (a->y) + (a->z) * (a->z));
    return out;
}

YK_Vec3f yk_vec3f_normalize(const YK_Vec3f *a)
{
    YK_Vec3f out;
    out = yk_math_vec3f_div_s(a, yk_vec3f_length(a));
    return out;
}

void yk_vec3f_print(const YK_Vec3f *a)
{
    printf("x: %f y: %f z: %f\n", a->x, a->y, a->z);
}

void yk_vec3f_mem_set(YK_Vec3f *a, f4 val)
{
    a->x = val;
    a->y = val;
    a->z = val;
}

/*
vec/scalar
*/

YK_Vec3f yk_math_vec3f_add_s(const YK_Vec3f *a, const f4 b)
{
    YK_Vec3f out;
    out.x = a->x + b;
    out.y = a->y + b;
    out.z = a->z + b;
    return out;
}
YK_Vec3f yk_math_vec3f_sub_s(const YK_Vec3f *a, const f4 b)
{
    YK_Vec3f out;
    out.x = a->x - b;
    out.y = a->y - b;
    out.z = a->z - b;
    return out;
}
YK_Vec3f yk_math_vec3f_mul_s(const YK_Vec3f *a, const f4 b)
{
    YK_Vec3f out;
    out.x = a->x * b;
    out.y = a->y * b;
    out.z = a->z * b;
    return out;
}
YK_Vec3f yk_math_vec3f_div_s(const YK_Vec3f *a, const f4 b)
{
    YK_Vec3f out;
    out.x = a->x / b;
    out.y = a->y / b;
    out.z = a->z / b;
    return out;
}

/*
vec/vec
*/

YK_Vec3f yk_math_vec3f_add(const YK_Vec3f *a, const YK_Vec3f *b)
{
    YK_Vec3f out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    out.z = a->z + b->z;
    return out;
}
YK_Vec3f yk_math_vec3f_sub(const YK_Vec3f *a, const YK_Vec3f *b)
{
    YK_Vec3f out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    out.z = a->z - b->z;
    return out;
}

f4 yk_math_vec3f_dot(const YK_Vec3f *a, const YK_Vec3f *b)
{
    f4 out;
    out = a->x * b->x + a->y * b->y + a->z * b->z;
    return out;
}
YK_Vec3f yk_math_vec3f_cross(const YK_Vec3f *a, const YK_Vec3f *b)
{
    YK_Vec3f out;
    out.x = a->y * b->z - a->z * b->y;
    out.y = a->z * b->x - a->x * b->z;
    out.z = a->x * b->y - a->y * b->x;
    return out;
}

/*
Vector4f
*/

void yk_vec4f_print(const YK_Vec4f *a)
{
    printf("x: %f y: %f z: %f\n", a->x, a->y, a->z);
}

void yk_vec4f_print_w(const YK_Vec4f *a)
{
    printf("x: %f y: %f z: %f w: %f\n", a->x, a->y, a->z, a->w);
}