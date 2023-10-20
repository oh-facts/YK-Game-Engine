#ifndef YK_MATH_H
#define YK_MATH_H

#include <yk/math/yk_vector.h>
#include <yk/math/yk_matrix.h>
#include <yk/math/yk_math_common.h>
#include <yk/math/yk_math_types.h>
#include <yk/math/yk_math_transform.h>

#endif


/*
Note 1: 
        After lots of benchmarking and thorough research (for 3 whole days non stop), I have
        decided that manual SIMD adds no value to even 4x4 matrix manipulations. The compiler's
        vectorization is just as good (not better, just as good. I compared assembly) at -O3 flags.
*/