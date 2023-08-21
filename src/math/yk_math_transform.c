#include <yk_math_transform.h>

void yk_transform_translate(YK_Mat4f *mat, const YK_Vec3f *vec)
{
    //Better to make translation and multiply or directly?
    mat->m30 += mat->m00 * vec->x + mat->m10 * vec->y + mat->m20 * vec->z;
    mat->m31 += mat->m01 * vec->x + mat->m11 * vec->y + mat->m21 * vec->z;
    mat->m32 += mat->m02 * vec->x + mat->m12 * vec->y + mat->m22 * vec->z;
}
void yk_transform_rotate(YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis)
{
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;

    float x = axis->x;
    float y = axis->y;
    float z = axis->z;

    mat->m00 = t * x * x + c;
    mat->m01 = t * x * y - s * z;
    mat->m02 = t * x * z + s * y;

    mat->m10 = t * x * y + s * z;
    mat->m11 = t * y * y + c;
    mat->m12 = t * y * z - s * x;

    mat->m20 = t * x * z - s * y;
    mat->m21 = t * y * z + s * x;
    mat->m22 = t * z * z + c;
}

void yk_transform_scale(YK_Mat4f *mat, const YK_Vec3f *scale)
{
    /*
    YK_Mat4f scaleMat = {
        scale->x, 0.0f, 0.0f, 0.0f,
        0.0f, scale->y, 0.0f, 0.0f,
        0.0f, 0.0f, scale->z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    *mat = yk_math_mat4f_mul_mat4f(mat, &scaleMat);
    */

    mat->m00 *= scale->x;
    mat->m01 *= scale->x;
    mat->m02 *= scale->x;

    mat->m10 *= scale->y;
    mat->m11 *= scale->y;
    mat->m12 *= scale->y;

    mat->m20 *= scale->z;
    mat->m21 *= scale->z;
    mat->m22 *= scale->z;

    // which method is better?
}