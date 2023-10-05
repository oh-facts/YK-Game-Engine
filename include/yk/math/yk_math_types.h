#ifndef YK_MATH_TYPES_H
#define YK_MATH_TYPES_H

#include <yk/yk_core_types.h>

typedef struct v2i
{
    i4 x, y;

} v2i;

typedef union v2f
{
    struct
    {
        f4 x, y;
    };
    struct
    {
        f4 u,v;
    };

} v2f;

typedef struct v3f
{
    struct
    {
        f4 x, y, z;
    };
    struct
    {
        f4 r, g, b;
    };
    
} v3f;

typedef union v4f
{
    struct
    {
        f4 x, y, z, w;
    };
    struct
    {
        f4 r, g, b, a;
    };
} v4f;

typedef struct m4f
{
    f4 m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33;
} m4f;


/*
Stores pos, rot and scale
*/
typedef struct YK_Transform
{
    v3f pos;
    v3f rot;
    v3f scale;
} YK_Transform;

typedef struct YK_Transform2d
{
    v2f pos;
    f4 rot_z;
    v2f scale;
} YK_Transform2d;

#endif