#include <yk_math_transform.h>


YK_Mat4f yk_transform_translate(const YK_Mat4f *mat, const YK_Vec3f *vec)
{
    YK_Mat4f out = *mat;
    out.m03 += vec->x;
    out.m13 += vec->y;
    out.m23 += vec->z;
    return out;
}

YK_Mat4f yk_transform_rotate(const YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis)
{
    return *mat;
}
YK_Mat4f yk_transform_scale(const YK_Mat4f *mat, const YK_Vec3f *scale)
{
    YK_Mat4f out = *mat;
    out.m00 *= scale->x;
    out.m11 *= scale->y;
    out.m22 *= scale->z;
    return out;

}