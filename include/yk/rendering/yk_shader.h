#ifndef YK_SHADER_H
#define YK_SHADER_H

#include <yk/yk_core_types.h>
#include <yk/yk_file_reader.h>

/*
    Creates a shader
*/
i4 yk_shader_create(const char *vertexFile, const char *fragmentFile);  

#endif