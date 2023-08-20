#ifndef YK_MATH_TRANFORM_H
#define YK_MATH_TRANFORM_H

#include <yk_math_common.h>
#include <yk_matrix.h>
#include <yk_vector.h>


void yk_transform_translate(YK_Mat4f *mat, const YK_Vec3f *vec);
void yk_transform_rotate(YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis);
void yk_transform_scale(YK_Mat4f *mat, const YK_Vec3f *scale);

/*
Can't decide if I want to keep them pure and return YK_Mat4f objects, or keep them non const and void
*/

#endif