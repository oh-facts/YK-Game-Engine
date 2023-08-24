#ifndef YK_RENDERER_H
#define YK_RENDERER_H

#include <glad/glad.h>

typedef struct YK_Sprite
{
    GLuint shaderProgram;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint texture;
} YK_Sprite;

GLuint yk_shader_create(const char *vertexFile, const char *fragmentFile);

YK_Sprite yk_sprite_create(const char *imageFile);
void yk_sprite_cleanup(YK_Sprite *sprite);

YK_Sprite yk_cube_create(const char *imageFile);
void yk_cube_cleanup(YK_Sprite *sprite);

void yk_render_sprite(YK_Sprite *sprite);
void yk_render_cube(YK_Sprite *sprite);

void yk_renderer_update();

#endif