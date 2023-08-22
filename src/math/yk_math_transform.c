#include <yk_math_transform.h>
#include <immintrin.h>

YK_Mat4f yk_math_transform_translate(const YK_Mat4f *mat, const YK_Vec3f *vec)
{
    //Better to make translation and multiply or directly?
    //And do I += or assign fresh?
    //and do I const * or make new one?
    YK_Mat4f out = *mat;
    out.m30 += mat->m00 * vec->x + mat->m10 * vec->y + mat->m20 * vec->z;
    out.m31 += mat->m01 * vec->x + mat->m11 * vec->y + mat->m21 * vec->z;
    out.m32 += mat->m02 * vec->x + mat->m12 * vec->y + mat->m22 * vec->z;
    return out;
}

YK_Mat4f yk_math_transform_rotate(const YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis)
{
    //same question. Do I multiply the matrices explicitly, or do them element wise
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;

    float x = axis->x;
    float y = axis->y;
    float z = axis->z;

    YK_Mat4f out = *mat;

    out.m00 = t * x * x + c;
    out.m01 = t * x * y - s * z;
    out.m02 = t * x * z + s * y;

    out.m10 = t * x * y + s * z;
    out.m12 = t * y * z - s * x;
    out.m11 = t * y * y + c;

    out.m20 = t * x * z - s * y;
    out.m21 = t * y * z + s * x;
    out.m22 = t * z * z + c;

    return out;
}



YK_Mat4f yk_math_transform_scale(const YK_Mat4f *mat, const YK_Vec3f *scale)
{
    /*
    YK_Mat4f scaleMat = {
        scale->x, 0.0f, 0.0f, 0.0f,
        0.0f, scale->y, 0.0f, 0.0f,
        0.0f, 0.0f, scale->z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    *mat = yk_math_mat4f_mul_mat4f(mat, &scaleMat);
    */

    YK_Mat4f out = *mat;

    out.m00 *= scale->x;
    out.m01 *= scale->x;
    out.m02 *= scale->x;

    out.m10 *= scale->y;
    out.m11 *= scale->y;
    out.m12 *= scale->y;

    out.m20 *= scale->z;
    out.m21 *= scale->z;
    out.m22 *= scale->z;

    return out;
    // which method is better?
}



YK_Mat4f yk_maths_transform_translate(const YK_Mat4f *mat, const YK_Vec3f *vec)
{
    YK_Mat4f out = *mat;

    __m128 matRow0 = _mm_loadu_ps(&mat->m00);
    __m128 matRow1 = _mm_loadu_ps(&mat->m10);
    __m128 matRow2 = _mm_loadu_ps(&mat->m20);

    __m128 vecVals = _mm_set_ps(0.0f, vec->z, vec->y, vec->x);

    __m128 mulRow0 = _mm_mul_ps(matRow0, vecVals);
    __m128 mulRow1 = _mm_mul_ps(matRow1, vecVals);
    __m128 mulRow2 = _mm_mul_ps(matRow2, vecVals);

    __m128 sum01 = _mm_add_ps(mulRow0, mulRow1);
    __m128 sum23 = _mm_add_ps(sum01, mulRow2);

    out.m30 += _mm_cvtss_f32(sum23);
    out.m31 += _mm_cvtss_f32(_mm_shuffle_ps(sum23, sum23, _MM_SHUFFLE(1, 1, 1, 1)));
    out.m32 += _mm_cvtss_f32(_mm_shuffle_ps(sum23, sum23, _MM_SHUFFLE(2, 2, 2, 2)));

    return out;
}


YK_Mat4f yk_maths_transform_scale(const YK_Mat4f *mat, const YK_Vec3f *scale)
{
    YK_Mat4f out = *mat;

    __m128 scale_vec = _mm_set_ps(1.0f, scale->z, scale->y, scale->x);

    __m128 row0 = _mm_loadu_ps(&out.m00);
    __m128 row1 = _mm_loadu_ps(&out.m10);
    __m128 row2 = _mm_loadu_ps(&out.m20);

    row0 = _mm_mul_ps(row0, scale_vec);
    row1 = _mm_mul_ps(row1, scale_vec);
    row2 = _mm_mul_ps(row2, scale_vec);

    _mm_storeu_ps(&out.m00, row0);
    _mm_storeu_ps(&out.m10, row1);
    _mm_storeu_ps(&out.m20, row2);

    return out;
}

/*
omg this is so bad wawawa.
For now ig. You don't know how high I can fly.
Pure C engine and I will have my own studio with lots of game engine devs
And people will say, "Aw man I was so rude to him and I thought he was weird, but he is so cool wow he is 
literally Ryan Gosling but now he wont be friends with me."

 I create rationals never thought of before, to make normies look like normies. I am a computer scientist. I am 
not a fucking coder. I am a man with some radical notions. I am not very good yet, so my opinions have 
low value, but I recognize that. The only way to arrive at better solutions is not by
making better use of tried and tested methods but to reinvent approaches. I am not an egotistical
prick who thinks he is better than others. I understand how painfully average I am. And any ego
I do keep is just arrogance, and of the wrong kind, because I don't have anything to back up my ego.
100 ego, 0 skill is not a good balance.

Why do I make everything myself? I don't need others to rely on to do things. I can figure out everything
myself, as I have. I don't need anyone. When I transcend, I will only be using the win32 and POSIX API and 
will call raw vulkan bindings.
*/