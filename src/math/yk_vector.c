#include <yk/math/yk_vector.h>

/*
Vector2f
*/
f4 yk_vec2f_length(const v2f *a)
{
    f4 out;
    out = sqrtf((a->x) * (a->x) + (a->y) * (a->y));

    return out;
}

v2f yk_vec2f_normalize(const v2f *a)
{
    v2f out;
    out = yk_math_vec2f_div_s(a, yk_vec2f_length(a));

    return out;
}

void yk_vec2f_print(const v2f *a)
{
    printf("x: %f y: %f\n", a->x, a->y);
}

/*
vec/scalar
*/

v2f yk_math_vec2f_add_s(const v2f *a, const f4 b)
{
    v2f out;
    out.x = a->x + b;
    out.y = a->y + b;
    return out;
}
v2f yk_math_vec2f_sub_s(const v2f *a, const f4 b)
{
    v2f out;
    out.x = a->x - b;
    out.y = a->y - b;
    return out;
}
v2f yk_math_vec2f_mul_s(const v2f *a, const f4 b)
{
    v2f out;
    out.x = a->x * b;
    out.y = a->y * b;
    return out;
}
v2f yk_math_vec2f_div_s(const v2f *a, const f4 b)
{
    v2f out;
    out.x = a->x / b;
    out.y = a->y / b;
    return out;
}
/*
vec/vec
*/

v2f yk_math_vec2f_add(const v2f *a, const v2f *b)
{
    v2f out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    return out;
}

v2f yk_math_vec2f_sub(const v2f *a, const v2f *b)
{
    v2f out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    return out;
}

/*
Vector3f
*/

f4 yk_vec3f_length(const v3f *a)
{
    f4 out;
    out = sqrtf((a->x) * (a->x) + (a->y) * (a->y) + (a->z) * (a->z));
    return out;
}

v3f yk_vec3f_normalize(const v3f *a)
{
    v3f out;
    out = yk_math_vec3f_div_s(a, yk_vec3f_length(a));
    return out;
}

void yk_vec3f_print(const v3f *a)
{
    printf("x: %f y: %f z: %f\n", a->x, a->y, a->z);
}

void yk_vec3f_mem_set(v3f *a, f4 val)
{
    a->x = val;
    a->y = val;
    a->z = val;
}

/*
vec/scalar
*/

v3f yk_math_vec3f_add_s(const v3f *a, const f4 b)
{
    v3f out;
    out.x = a->x + b;
    out.y = a->y + b;
    out.z = a->z + b;
    return out;
}
v3f yk_math_vec3f_sub_s(const v3f *a, const f4 b)
{
    v3f out;
    out.x = a->x - b;
    out.y = a->y - b;
    out.z = a->z - b;
    return out;
}
v3f yk_math_vec3f_mul_s(const v3f *a, const f4 b)
{
    v3f out;
    out.x = a->x * b;
    out.y = a->y * b;
    out.z = a->z * b;
    return out;
}
v3f yk_math_vec3f_div_s(const v3f *a, const f4 b)
{
    v3f out;
    out.x = a->x / b;
    out.y = a->y / b;
    out.z = a->z / b;
    return out;
}

/*
vec/vec
*/

v3f yk_math_vec3f_add(const v3f *a, const v3f *b)
{
    v3f out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    out.z = a->z + b->z;
    return out;
}
v3f yk_math_vec3f_sub(const v3f *a, const v3f *b)
{
    v3f out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    out.z = a->z - b->z;
    return out;
}

f4 yk_math_vec3f_dot(const v3f *a, const v3f *b)
{
    f4 out;
    out = a->x * b->x + a->y * b->y + a->z * b->z;
    return out;
}
v3f yk_math_vec3f_cross(const v3f *a, const v3f *b)
{
    v3f out;
    out.x = a->y * b->z - a->z * b->y;
    out.y = a->z * b->x - a->x * b->z;
    out.z = a->x * b->y - a->y * b->x;
    return out;
}

/*
Vector4f
*/

void yk_vec4f_print(const v4f *a)
{
    printf("x: %f y: %f z: %f\n", a->x, a->y, a->z);
}

void yk_vec4f_print_w(const v4f *a)
{
    printf("x: %f y: %f z: %f w: %f\n", a->x, a->y, a->z, a->w);
}