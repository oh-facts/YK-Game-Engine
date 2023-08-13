#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>


typedef struct Sprite
{
    GLuint shaderProgram;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint texture;
} Sprite;

GLuint create_shader(const char *vertexFile, const char *fragmentFile);

Sprite create_sprite(const char *imageFile);
void render_sprite(Sprite *sprite);
void cleanup_sprite(Sprite *sprite);

void renderer_update();

#endif