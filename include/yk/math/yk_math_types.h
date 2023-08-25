#ifndef YK_MATH_TYPES_H
#define YK_MATH_TYPES_H

#include <yk/yk_core_types.h>



typedef struct YK_Vec2i
{
    i4 x, y;

} YK_Vec2i;


typedef struct YK_Vec2f
{
    f4 x, y;

} YK_Vec2f;

typedef struct YK_Vec3f
{
    f4 x, y, z;

} YK_Vec3f;

typedef struct YK_Vec4f
{
    f4 x, y, z, w;

} YK_Vec4f;


typedef struct YK_Mat4f
{
    f4 m00, m01, m02, m03,
       m10, m11, m12, m13,
       m20, m21, m22, m23,
       m30, m31, m32, m33;
} YK_Mat4f;



#endif