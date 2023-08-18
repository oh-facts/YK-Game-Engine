#ifndef YK_MATRIX_C
#define YK_MATRIX_C

#include <yk_matrix.h>


YK_Mat4f yk_mat4f_scalar(const f4 diagonal)
{
     YK_Mat4f out = {
        .m00 = diagonal, .m01 = 0.0f, .m02 = 0.0f, .m03 = 0.0f,
        .m10 = 0.0f, .m11 = diagonal, .m12 = 0.0f, .m13 = 0.0f,
        .m20 = 0.0f, .m21 = 0.0f, .m22 = diagonal, .m23 = 0.0f,
        .m30 = 0.0f, .m31 = 0.0f, .m32 = 0.0f, .m33 = diagonal
    };

    return out;
}


YK_Mat4f yk_mat4f_translate(const YK_Mat4f *mat, const YK_Vec3f *vec)
{
    YK_Mat4f out = *mat;
    out.m03 += vec->x;
    out.m13 += vec->y;
    out.m23 += vec->z;
    return out;
}


/*
vec/mat
*/
YK_Vec4f yk_math_mat4f_mul_vec4f(const YK_Mat4f *mat, const YK_Vec4f *vec)
{
    YK_Vec4f out;
    out.x = mat->m00 * vec->x + mat->m01 * vec->y + mat->m02 * vec->z + mat->m03 * vec->w;
    out.y = mat->m10 * vec->x + mat->m11 * vec->y + mat->m12 * vec->z + mat->m13 * vec->w;
    out.z = mat->m20 * vec->x + mat->m21 * vec->y + mat->m22 * vec->z + mat->m23 * vec->w;
    out.w = mat->m30 * vec->x + mat->m31 * vec->y + mat->m32 * vec->z + mat->m33 * vec->w;

    return out;
}

#endif