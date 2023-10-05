/*
Need someone with experience to verify SIMD code. I ran "benchmarks". Result: SIMD is slightly better.
Notable observation: My regular implementation might be so bad, that my SIMD appears better.
*/

#ifndef YK_MATH_TRANFORM_H
#define YK_MATH_TRANFORM_H

#include <yk/math/yk_math_common.h>
#include <yk/math/yk_matrix.h>
#include <yk/math/yk_vector.h>


void yk_math_transform_translate(m4f *mat, const v3f *vec);
void yk_math_transform_rotate(m4f *mat, const f4 angle, const v3f *axis);
void yk_math_transform_scale(m4f *mat, const v3f *scale);

//plural because they are doing more maths  (joke. S is SIMD)
//https://www.youtube.com/shorts/pz7Q9U7A1dw

void yk_maths_transform_translate(m4f *mat, const v3f *vec);
void yk_maths_transform_rotate(m4f *mat, const f4 angle, const v3f *axis);
void yk_maths_transform_scale(m4f *mat, const v3f *scale);


//My SIMD for rotate just wouldn't work.

#endif