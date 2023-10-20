#ifndef YK_SHADER_H
#define YK_SHADER_H

#include <glad/glad.h>
#include <yk/yk_file_reader.h>

/*
    Creates a shader
*/
GLuint yk_shader_create(const char *vertexFile, const char *fragmentFile);  

#endif