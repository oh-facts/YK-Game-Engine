#ifndef YK_MATRIX_H
#define YK_MATRIX_H

#include <yk_math_types.h>


YK_Mat4f yk_mat4f_scalar(const f4 diagonal);
YK_Mat4f yk_mat4f_translate(const YK_Mat4f *mat, const YK_Vec3f *vec);


/*
vec/matrix
*/
YK_Vec4f yk_math_mul_mat4f_vec4f(const YK_Mat4f *mat, const YK_Vec4f *vec);

#endif