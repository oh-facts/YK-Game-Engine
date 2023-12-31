#ifndef YK_MATRIX_H
#define YK_MATRIX_H

#include <yk/math/yk_math_types.h>

/*
    returns a zeroed 4x4 float matrix
*/
m4f yk_mat4f_zero();

/*
    returns an Identity 4x4 float matrix
*/
m4f yk_mat4f_identity();

/*
    returns a scalar 4x4 float matrix
*/
m4f yk_mat4f_scalar(const f4 diagonal);

/*
    returns an orthographic matrix
*/
m4f yk_mat4f_ortho(const f4 left, const f4 right, const f4 bottom, const f4 top, const f4 near, const f4 far);

/*
    returns a perspective matrix
*/
m4f yk_mat4f_perspective(const f4 fov_degrees, const f4 aspect_ratio, const f4 near, const f4 far);

/*
    prints a matrix
*/
void yk_mat4f_print(const m4f *a);

/*
vec/matrix
*/

/*
    4x4 matrix  x  vec4
*/
v4f yk_math_mat4f_mul_vec4f(const m4f *mat, const v4f *vec);

/*
    4x4 matrix  x  4x4 matrix
*/
m4f yk_math_mat4f_mul_mat4f(const m4f *mat1, const m4f *mat2);

/*
    returns a matrix that looks at target, from eye
*/
m4f yk_look_at(const v3f *eye, const v3f *target, const v3f *up);

#endif