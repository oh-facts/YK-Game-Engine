#ifndef YK_RENDERER2D_H
#define YK_RENDERER2D_H

#include <glad/glad.h>
#include <yk/yk_camera2d.h>
#include <yk/math/yk_math.h>
#include <yk/yk_shader.h>
#include <yk/yk_texture.h>

// for a 2d renderer, only an ortho camera makes sense. if you want to do 3d stuff pr funky 2d stuff like
// perspective, then use a 3d camera/renderer.

/*
typedef struct YK_Rect
{
    GLuint shaderProgram;
    GLuint vertex_arrays;

    YK_Mat4f model_mat;
    YK_Vec3f pos;
} YK_Rect;

typedef struct YK_Sprite
{
    YK_Rect rect;
    YK_Texture texture;
} YK_Sprite;
*/

typedef struct YK_Sprite
{
    GLuint shaderProgram;
    GLuint vertex_arrays;

    YK_Mat4f model_mat;
    YK_Vec3f pos;

    YK_Texture texture;
} YK_Sprite;

typedef struct YK_Renderer2d
{
    /*
        Current camera2d reference. Cameras are "owned" by the app. The
        app creates them and the renderer can choose which camera to render
        to. Soon enough there will be a viewport to offload some duties to.
    */
    YK_Camera2d *current_cam;

    YK_Mat4f view_mat;

    YK_Mat4f proj_mat;
} YK_Renderer2d;

// YK_Rect yk_renderer2d_create_rect();
// void yk_renderer2d_destroy_rect(YK_Rect *rect);

YK_Sprite yk_sprite_create(const char *texture_path);
void yk_sprite_destroy(YK_Sprite *sprite);
void yk_sprite_set_pos(YK_Sprite *sprite, YK_Vec3f *pos);

// void yk_renderer2d_
void yk_renderer2d_render_sprite(YK_Renderer2d *renderer, YK_Sprite *sprite);

void yk_sprite_set_texture(const char *texture_path);

void yk_renderer2d_innit(YK_Renderer2d *renderer, YK_Camera2d *current_cam, YK_Window *win);
void yk_renderer2d_run(YK_Renderer2d *renderer, YK_Window *win);

#endif