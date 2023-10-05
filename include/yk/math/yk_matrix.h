#ifndef YK_MATRIX_H
#define YK_MATRIX_H

#include <yk/math/yk_math_types.h>

YK_Mat4f yk_mat4f_zero();
YK_Mat4f yk_mat4f_identity();
YK_Mat4f yk_mat4f_scalar(const f4 diagonal);

YK_Mat4f yk_mat4f_ortho(const f4 left, const f4 right, const f4 bottom, const f4 top, const f4 near, const f4 far);
YK_Mat4f yk_mat4f_perspective(const f4 fov_degrees, const f4 aspect_ratio, const f4 near, const f4 far);
void yk_mat4f_print(const YK_Mat4f *a);

/*
vec/matrix
*/
YK_Vec4f yk_math_mat4f_mul_vec4f(const YK_Mat4f *mat, const YK_Vec4f *vec);

YK_Mat4f yk_math_mat4f_mul_mat4f(const YK_Mat4f *mat1, const YK_Mat4f *mat2);

YK_Mat4f yk_look_at(const YK_Vec3f *eye, const YK_Vec3f *target, const YK_Vec3f *up);

#endif