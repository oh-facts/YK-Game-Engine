#include <yk_math_transform.h>

void yk_transform_translate(YK_Mat4f *mat, const YK_Vec3f *vec)
{
    mat->m03 += vec->x;
    mat->m13 += vec->y;
    mat->m23 += vec->z;
}
void yk_transform_rotate(YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis)
{
    f4 c = cos(angle);
    f4 s = sin(angle);
    f4 t = 1.0f - c;

    f4 x = axis->x;
    f4 y = axis->y;
    f4 z = axis->z;

    // Normalize the axis vector
    f4 length = sqrt(x * x + y * y + z * z);
    if (length != 0.0f)
    {
        f4 invLength = 1.0f / length;
        x *= invLength;
        y *= invLength;
        z *= invLength;
    }

    f4 x2 = x * x;
    f4 y2 = y * y;
    f4 z2 = z * z;

    f4 xy = x * y;
    f4 xz = x * z;
    f4 yz = y * z;

    f4 txy = t * xy;
    f4 txz = t * xz;
    f4 tyz = t * yz;

    f4 tsx = t * x * s;
    f4 tsy = t * y * s;
    f4 tsz = t * z * s;

    f4 m00 = t * x2 + c;
    f4 m01 = txy - tsz;
    f4 m02 = txz + tsy;

    f4 m10 = txy + tsz;
    f4 m11 = t * y2 + c;
    f4 m12 = tyz - tsx;

    f4 m20 = txz - tsy;
    f4 m21 = tyz + tsx;
    f4 m22 = t * z2 + c;

   
    YK_Mat4f temp = *mat;
    mat->m00 = temp.m00 * m00 + temp.m10 * m01 + temp.m20 * m02;
    mat->m01 = temp.m01 * m00 + temp.m11 * m01 + temp.m21 * m02;
    mat->m02 = temp.m02 * m00 + temp.m12 * m01 + temp.m22 * m02;

    mat->m10 = temp.m00 * m10 + temp.m10 * m11 + temp.m20 * m12;
    mat->m11 = temp.m01 * m10 + temp.m11 * m11 + temp.m21 * m12;
    mat->m12 = temp.m02 * m10 + temp.m12 * m11 + temp.m22 * m12;

    mat->m20 = temp.m00 * m20 + temp.m10 * m21 + temp.m20 * m22;
    mat->m21 = temp.m01 * m20 + temp.m11 * m21 + temp.m21 * m22;
    mat->m22 = temp.m02 * m20 + temp.m12 * m21 + temp.m22 * m22;


}

void yk_transform_scale(YK_Mat4f *mat, const YK_Vec3f *scale)
{
  
    mat->m00 *= scale->x;
    mat->m11 *= scale->y;
    mat->m22 *= scale->z;

}