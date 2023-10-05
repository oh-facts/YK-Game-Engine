#ifndef YK_MATH_TYPES_H
#define YK_MATH_TYPES_H

#include <yk/yk_core_types.h>

typedef struct YK_Vec2i
{
    i4 x, y;

} YK_Vec2i;

typedef union YK_Vec2f
{
    struct
    {
        f4 x, y;
    };
    struct
    {
        f4 u,v;
    };

} YK_Vec2f;

typedef struct YK_Vec3f
{
    struct
    {
        f4 x, y, z;
    };
    struct
    {
        f4 r, g, b;
    };
    
} YK_Vec3f;

typedef union YK_Vec4f
{
    struct
    {
        f4 x, y, z, w;
    };
    struct
    {
        f4 r, g, b, a;
    };
} YK_Vec4f;

typedef struct YK_Mat4f
{
    f4 m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33;
} YK_Mat4f;


/*
Stores pos, rot and scale
*/
typedef struct YK_Transform
{
    YK_Vec3f pos;
    YK_Vec3f rot;
    YK_Vec3f scale;
} YK_Transform;

#endif