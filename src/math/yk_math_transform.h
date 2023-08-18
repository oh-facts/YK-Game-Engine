#ifndef YK_MATH_TRANFORM_H
#define YK_MATH_TRANFORM_H

#include <yk_math_common.h>


YK_Mat4f yk_transform_translate(const YK_Mat4f *mat, const YK_Vec3f *vec);
YK_Mat4f yk_transform_rotate(const YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis);
YK_Mat4f yk_transform_scale(const YK_Mat4f *mat, const YK_Vec3f *scale);

#endif