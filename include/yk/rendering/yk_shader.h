#ifndef YK_SHADER_H
#define YK_SHADER_H

#include <yk/yk_core_types.h>
#include <yk/yk_file_reader.h>

/*
    Returns a vertex and fragment shader program id.
    The returned id needs to be freed with glDeleteProgram.
    
    Any shader compiling/linking errors are printed to the console
*/
u4 yk_shader_program_create_vertex_fragment(const char *vertexFile, const char *fragmentFile);

#endif