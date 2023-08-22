/*
Need someone with experience to verify SIMD code. I ran "benchmarks". Result: SIMD is slightly better.
Notable observation: My regular implementation might be so bad, that my SIMD appears better.
*/

#ifndef YK_MATH_TRANFORM_H
#define YK_MATH_TRANFORM_H

#include <yk_math_common.h>
#include <yk_matrix.h>
#include <yk_vector.h>


YK_Mat4f yk_math_transform_translate(const YK_Mat4f *mat, const YK_Vec3f *vec);
YK_Mat4f yk_math_transform_rotate(const YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis);
YK_Mat4f yk_math_transform_scale(const YK_Mat4f *mat, const YK_Vec3f *scale);

//plural because they are doing more maths  (joke. S is SIMD)
//https://www.youtube.com/shorts/pz7Q9U7A1dw

YK_Mat4f yk_maths_transform_translate(const YK_Mat4f *mat, const YK_Vec3f *vec);
YK_Mat4f yk_maths_transform_rotate(const YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis);
YK_Mat4f yk_maths_transform_scale(const YK_Mat4f *mat, const YK_Vec3f *scale);


//My SIMD for rotate just wouldn't work

#endif