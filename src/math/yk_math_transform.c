#include <yk_math_transform.h>
#include <immintrin.h>

void yk_math_transform_translate(YK_Mat4f *mat, const YK_Vec3f *vec)
{
    // Better to make translation and multiply or directly?
    // And do I += or assign fresh?
    // and do I const * or make new one?
    mat->m30 += mat->m00 * vec->x + mat->m10 * vec->y + mat->m20 * vec->z;
    mat->m31 += mat->m01 * vec->x + mat->m11 * vec->y + mat->m21 * vec->z;
    mat->m32 += mat->m02 * vec->x + mat->m12 * vec->y + mat->m22 * vec->z;
}

void yk_math_transform_rotate(YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis)
{
    // same question. Do I multiply the matrices explicitly, or do them element wise
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;

    YK_Vec3f _axis = yk_vec3f_normalize(axis);
    float x = _axis.x;
    float y = _axis.y;
    float z = _axis.z;

    mat->m00 = t * x * x + c;
    mat->m01 = t * x * y - s * z;
    mat->m02 = t * x * z + s * y;

    mat->m10 = t * x * y + s * z;
    mat->m12 = t * y * z - s * x;
    mat->m11 = t * y * y + c;

    mat->m20 = t * x * z - s * y;
    mat->m21 = t * y * z + s * x;
    mat->m22 = t * z * z + c;

}

void yk_math_transform_scale(YK_Mat4f *mat, const YK_Vec3f *scale)
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
void yk_maths_transform_translate(YK_Mat4f *mat, const YK_Vec3f *vec)
{
    __m128 vec_data = _mm_loadu_ps((float *)vec);
    __m128 row0 = _mm_loadu_ps(&mat->m00);
    __m128 row1 = _mm_loadu_ps(&mat->m10);
    __m128 row2 = _mm_loadu_ps(&mat->m20);
    __m128 row3 = _mm_loadu_ps(&mat->m30);

    row3 = _mm_add_ps(row3, _mm_mul_ps(row0, vec_data));
    row3 = _mm_add_ps(row3, _mm_mul_ps(row1, vec_data));
    row3 = _mm_add_ps(row3, _mm_mul_ps(row2, vec_data));

    _mm_storeu_ps(&mat->m30, row3);
}
/*
*/

void yk_maths_transform_rotate(YK_Mat4f *mat, const f4 angle, const YK_Vec3f *axis)
{
    printf("Eeska meeska mickey mouse");
}


void yk_maths_transform_scale(YK_Mat4f *mat, const YK_Vec3f *scale)
{
    __m128 scale_vec = _mm_loadu_ps((float *)scale);

    __m128 row0 = _mm_loadu_ps(&mat->m00);
    __m128 row1 = _mm_loadu_ps(&mat->m10);
    __m128 row2 = _mm_loadu_ps(&mat->m20);

    row0 = _mm_mul_ps(row0, scale_vec);
    row1 = _mm_mul_ps(row1, scale_vec);
    row2 = _mm_mul_ps(row2, scale_vec);

    _mm_storeu_ps(&mat->m00, row0);
    _mm_storeu_ps(&mat->m10, row1);
    _mm_storeu_ps(&mat->m20, row2);
}

/*
omg this is so bad wawawa.
For now ig. You don't know how high I can fly.
Pure C engine and I will have my own studio with lots of game engine devs
And people will say, "Aw man I was so rude to him and I thought he was weird, but he is so cool wow he is
literally Ryan Gosling but now he wont be friends with me."

I create rationals never imagined before, to make normies look like normies. I am a computer scientist. I am
not a fucking coder. I am a man with some radical notions. I am not very good yet, so my opinions have
low value, but I recognize that. The only way to arrive at better solutions is not by
making better use of tried and tested methods but to reinvent approaches. I am not an egotistical
prick who thinks he is better than others. I understand how painfully average I am. And any ego
I do keep is just arrogance, and of the wrong kind, because I don't have anything to back up my ego.
Ego is fine if you're actually a genius.

Why do I make everything myself? I don't need others to rely on to do things. I can figure out everything
myself, as I have. I don't need anyone. When I transcend, I will only be using the win32 and POSIX API and
will call raw vulkan bindings. Nobody will apreciate my methods, or ever read this, but thats fine, I don't
need validation to judge my worth.

Eventually I will have scientists forking my engine's physics and maths to run simulations. And web devs would
mention me by name in their suicide notes (joke)
*/