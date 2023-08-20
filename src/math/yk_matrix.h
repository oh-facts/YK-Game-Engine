#ifndef YK_MATRIX_H
#define YK_MATRIX_H

#include <yk_math_types.h>


YK_Mat4f yk_mat4f_scalar(const f4 diagonal);
void yk_mat4f_print(const YK_Mat4f *a);

/*
vec/matrix
*/
YK_Vec4f yk_math_mat4f_mul_vec4f(const YK_Mat4f *mat, const YK_Vec4f *vec);

YK_Mat4f yk_math_mat4f_mul_mat4f(const YK_Mat4f *mat1, const YK_Mat4f *mat2);

#endif