#ifndef YK_DATATYPES_H
#define YK_DATATYPES_H

#include <stdint.h>

/*
common primitive types aliased for readaiblity.
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

/*
Excuse me. What is this montrosity?
>Huh?
Monstrosity I mean
>Byte sizes are more intuitive to me? And smaller to write? (Not that I am trying to save time, but it seems more sensible?).
>I am always converting bit sizes to byte in my head when working with these, so I think byte is better? Refactoring would be very easy anyways, so unless
>someone can shed light, I will stick to this.
b1 b2 b4 b8??????. Just use Bool_
>Unless you are supporting your statements with logic, I am not interested in discussions.
*/

#endif