#ifndef YK_VECTOR_H
#define YK_VECTOR_H

#include <yk_math_types.h>


/*
Vector2f
*/

/*
vec/scalar
*/

YK_Vec2f yk_math_add_vec2f_s(const YK_Vec2f *a, const f4 b);
YK_Vec2f yk_math_sub_vec2f_s(const YK_Vec2f *a, const f4 b);

/*
vec/vec
*/

YK_Vec2f yk_math_add_vec2f(const YK_Vec2f *a, const YK_Vec2f *b);
YK_Vec2f yk_math_sub_vec2f(const YK_Vec2f *a, const YK_Vec2f *b);

/*
Vector3f
*/

/*
vec/scalar
*/

YK_Vec3f yk_math_add_vec3f_s(const YK_Vec3f *a, const f4 b);
YK_Vec3f yk_math_sub_vec3f_s(const YK_Vec3f *a, const f4 b);

/*
vec/vec
*/

YK_Vec3f yk_math_add_vec3f(const YK_Vec3f *a, const YK_Vec3f *b);
YK_Vec3f yk_math_sub_vec3f(const YK_Vec3f *a, const YK_Vec3f *b);




#endif