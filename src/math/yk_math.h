#ifndef YK_MATH_H
#define YK_MATH_H

#include <yk_vector.h>
#include <yk_matrix.h>
#include <yk_math_common.h>
#include <yk_math_types.h>
#include <yk_math_transform.h>

#endif


/*
Note 1: 
        After lots of benchmarking and thorough research (for 3 whole days non stop), I have
        decided that manual SIMD adds no value to even 4x4 matrix manipulations. The compiler's
        vectorization is just as good (not better, just as good. I compared assembly) at -O3 flags.
*/

/*
Note 2: 
        Excuse me good sir, why are you using const ref?
        ref because from what I learnt, from benchmarking and research, if size > void*, then pass by reference
        Use const so you don't accidentally change the value.
        Yes sir, but what about the performance hit from the pointer indirection?
        I compared assembly, even for the most basic scenario (vec2f + scalar), const ref was better,
        but ofc, feel free to test it yourself and if you're right, you can push a commit.

        Make sure to put maximum compiler optmizations before submitting a commit.
*/