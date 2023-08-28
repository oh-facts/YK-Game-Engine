#ifndef YK_RENDERER_H
#define YK_RENDERER_H

#include <glad/glad.h>
#include <yk/yk_camera.h>
#include <yk/math/yk_math.h>

typedef struct YK_Sprite
{
    GLuint shaderProgram;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint texture;
    YK_Mat4f model_mat;
    YK_Vec3f pos;
} YK_Sprite;


typedef struct YK_Renderer
{   
    /*
        Current camera reference. Cameras are "owned" by the app. The
        app creates them and the renderer can choose which camera to render
        to. 
    */
    YK_Camera *current_cam;

    YK_Mat4f view_mat;

    YK_Mat4f proj_mat;
} YK_Renderer;


GLuint yk_shader_create(const char *vertexFile, const char *fragmentFile);

YK_Sprite yk_sprite_create(const char *imageFile);
void yk_sprite_cleanup(YK_Sprite *sprite);

YK_Sprite yk_cube_create(const char *imageFile);
void yk_cube_set_pos(YK_Sprite *sprite, YK_Vec3f *pos);
void yk_cube_move(YK_Sprite *sprite, YK_Vec3f *pos);
void yk_cube_cleanup(YK_Sprite *sprite);

void yk_render_sprite(YK_Renderer *renderer, YK_Sprite *sprite);
void yk_render_cube(YK_Renderer *renderer, YK_Sprite *sprite);

void yk_renderer_innit(YK_Renderer *renderer, YK_Camera *current_cam);
void yk_renderer_run(YK_Renderer *renderer, YK_Window *win);

#endif