#ifndef YK_TEXTURE_H
#define YK_TEXTURE_H
#include <glad/glad.h>
#include <stb/stb_image.h>


typedef enum YK_Texture_format
{
    YK_TEXTURE_RGB = GL_RGB,
    YK_TEXTURE_RGBA = GL_RGBA

} YK_Texture_format;

typedef struct YK_Texture
{
    GLuint id;
    int width;
    int height;
    YK_Texture_format format;

} YK_Texture;

YK_Texture yk_texture_create(const char *path);

#endif