#ifndef YK_TEXTURE_H
#define YK_TEXTURE_H

#include <yk/yk_core_types.h>


typedef enum YK_Texture_format
{
    YK_TEXTURE_RGB,
    YK_TEXTURE_RGBA

} YK_Texture_format;

typedef struct YK_Texture
{
    u4 id;
    i4 width;
    i4 height;
    YK_Texture_format format;

} YK_Texture;

/*
    Creates a texture
*/
YK_Texture yk_texture_create(const char *path);

#endif