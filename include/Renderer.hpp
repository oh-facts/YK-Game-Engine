#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>


namespace AE
{

    unsigned int create_shader(const char *vertexFile, const char *fragmentFile);
    
} // namespace AE


#endif