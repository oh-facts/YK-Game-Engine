#ifndef YK_CORE_TYPES_H
#define YK_CORE_TYPES_H

#include <stdint.h>

/*
common primitive types and related constants aliased for readability.
size is in bytes
*/

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef int8_t i1;
typedef int16_t i2;
typedef int32_t i4;
typedef int64_t i8;

typedef float f4;
typedef double f8;

/*
Meant to be used as booleans
*/
typedef int8_t b1;
typedef int16_t b2;
typedef int32_t b4;
typedef int64_t b8;
#define false 0
#define true 1

#endif