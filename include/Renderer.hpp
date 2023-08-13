#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

namespace AE
{
    typedef struct Sprite
    {
        unsigned int shaderProgram;
        unsigned int vbo;
        unsigned int vao;
        unsigned int ebo;
        GLuint texture;
    } Sprite;

    unsigned int create_shader(const char *vertexFile, const char *fragmentFile);

    Sprite create_sprite(const char *imageFile);
    void render_sprite(Sprite &sprite);
    void cleanup_sprite(Sprite &sprite);

    void renderer_update();

} // namespace AE

#endif