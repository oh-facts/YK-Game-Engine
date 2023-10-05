#ifndef YK_VECTOR_H
#define YK_VECTOR_H

#include <yk/math/yk_math_common.h>


/*
Vector2f
*/

f4 yk_vec2f_length(const v2f a);
v2f yk_vec2f_normalize(const v2f a);
void yk_vec2f_print(const v2f a);

/*
vec/scalar
*/

v2f yk_math_vec2f_add_s(const v2f a, const f4 b);
v2f yk_math_vec2f_sub_s(const v2f a, const f4 b);
v2f yk_math_vec2f_mul_s(const v2f a, const f4 b);
v2f yk_math_vec2f_div_s(const v2f a, const f4 b);

/*
vec/vec
*/

v2f yk_math_vec2f_add(const v2f a, const v2f b);
v2f yk_math_vec2f_sub(const v2f a, const v2f b);

/*
Vector3f
*/

f4 yk_vec3f_length(const v3f a);
v3f yk_vec3f_normalize(const v3f a);
void yk_vec3f_print(const v3f a);
void yk_vec3f_mem_set(v3f a, f4 val);

/*
vec/scalar
*/

v3f yk_math_vec3f_add_s(const v3f a, const f4 b);
v3f yk_math_vec3f_sub_s(const v3f a, const f4 b);
v3f yk_math_vec3f_mul_s(const v3f a, const f4 b);
v3f yk_math_vec3f_div_s(const v3f a, const f4 b);

/*
vec/vec
*/

v3f yk_math_vec3f_add(const v3f a, const v3f b);
v3f yk_math_vec3f_sub(const v3f a, const v3f b);

f4 yk_math_vec3f_dot(const v3f a, const v3f b);
v3f yk_math_vec3f_cross(const v3f a, const v3f b);


/*
Vector4f
*/

void yk_vec4f_print(const v4f a);
void yk_vec4f_print_w(const v4f a);


#endif