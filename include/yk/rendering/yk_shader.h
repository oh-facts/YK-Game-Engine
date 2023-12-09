#ifndef YK_SHADER_H
#define YK_SHADER_H

#include <yk/yk_core_types.h>
#include <yk/yk_file_reader.h>

/*
    Returns a vertex and fragment shader program id.
    The returned id needs to be freed with glDeleteProgram.
    
    Any shader compiling/linking errors are printed to the console
*/
u4 yk_shader_vf_create(const char *vertexFile, const char *fragmentFile);

u4 yk_shader_comp_create(const char *computeFile);

#endif