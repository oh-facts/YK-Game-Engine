#ifndef YK_MATRIX_C
#define YK_MATRIX_C

#include <yk_matrix.h>

#include <stdio.h>

YK_Mat4f yk_mat4f_identity()
{
     YK_Mat4f out = {
        .m00 = 1.0f, .m01 = 0.0f, .m02 = 0.0f, .m03 = 0.0f,
        .m10 = 0.0f, .m11 = 1.0f, .m12 = 0.0f, .m13 = 0.0f,
        .m20 = 0.0f, .m21 = 0.0f, .m22 = 1.0f, .m23 = 0.0f,
        .m30 = 0.0f, .m31 = 0.0f, .m32 = 0.0f, .m33 = 1.0f
    };

    return out;
}

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

YK_Mat4f yk_math_mat4f_mul_mat4f(const YK_Mat4f *mat1, const YK_Mat4f *mat2)
{
    YK_Mat4f result;

    // Calculate the first row of the result matrix
    result.m00 = mat1->m00 * mat2->m00 + mat1->m01 * mat2->m10 + mat1->m02 * mat2->m20 + mat1->m03 * mat2->m30;
    result.m01 = mat1->m00 * mat2->m01 + mat1->m01 * mat2->m11 + mat1->m02 * mat2->m21 + mat1->m03 * mat2->m31;
    result.m02 = mat1->m00 * mat2->m02 + mat1->m01 * mat2->m12 + mat1->m02 * mat2->m22 + mat1->m03 * mat2->m32;
    result.m03 = mat1->m00 * mat2->m03 + mat1->m01 * mat2->m13 + mat1->m02 * mat2->m23 + mat1->m03 * mat2->m33;

    // Calculate the second row of the result matrix
    result.m10 = mat1->m10 * mat2->m00 + mat1->m11 * mat2->m10 + mat1->m12 * mat2->m20 + mat1->m13 * mat2->m30;
    result.m11 = mat1->m10 * mat2->m01 + mat1->m11 * mat2->m11 + mat1->m12 * mat2->m21 + mat1->m13 * mat2->m31;
    result.m12 = mat1->m10 * mat2->m02 + mat1->m11 * mat2->m12 + mat1->m12 * mat2->m22 + mat1->m13 * mat2->m32;
    result.m13 = mat1->m10 * mat2->m03 + mat1->m11 * mat2->m13 + mat1->m12 * mat2->m23 + mat1->m13 * mat2->m33;

    // Calculate the third row of the result matrix
    result.m20 = mat1->m20 * mat2->m00 + mat1->m21 * mat2->m10 + mat1->m22 * mat2->m20 + mat1->m23 * mat2->m30;
    result.m21 = mat1->m20 * mat2->m01 + mat1->m21 * mat2->m11 + mat1->m22 * mat2->m21 + mat1->m23 * mat2->m31;
    result.m22 = mat1->m20 * mat2->m02 + mat1->m21 * mat2->m12 + mat1->m22 * mat2->m22 + mat1->m23 * mat2->m32;
    result.m23 = mat1->m20 * mat2->m03 + mat1->m21 * mat2->m13 + mat1->m22 * mat2->m23 + mat1->m23 * mat2->m33;

    // Calculate the fourth row of the result matrix
    result.m30 = mat1->m30 * mat2->m00 + mat1->m31 * mat2->m10 + mat1->m32 * mat2->m20 + mat1->m33 * mat2->m30;
    result.m31 = mat1->m30 * mat2->m01 + mat1->m31 * mat2->m11 + mat1->m32 * mat2->m21 + mat1->m33 * mat2->m31;
    result.m32 = mat1->m30 * mat2->m02 + mat1->m31 * mat2->m12 + mat1->m32 * mat2->m22 + mat1->m33 * mat2->m32;
    result.m33 = mat1->m30 * mat2->m03 + mat1->m31 * mat2->m13 + mat1->m32 * mat2->m23 + mat1->m33 * mat2->m33;

    return result;
}
  void yk_mat4f_print(const YK_Mat4f *a) {

    printf("| %8.4f %8.4f %8.4f %8.4f |\n", a->m00, a->m01, a->m02, a->m03);
    printf("| %8.4f %8.4f %8.4f %8.4f |\n", a->m10, a->m11, a->m12, a->m13);
    printf("| %8.4f %8.4f %8.4f %8.4f |\n", a->m20, a->m21, a->m22, a->m23);
    printf("| %8.4f %8.4f %8.4f %8.4f |\n", a->m30, a->m31, a->m32, a->m33);
    printf("\n");

}


#endif