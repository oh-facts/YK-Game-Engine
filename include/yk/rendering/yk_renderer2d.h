#ifndef YK_RENDERER2D_H
#define YK_RENDERER2D_H

#include <glad/glad.h>
#include <yk/rendering/yk_camera2d.h>
#include <yk/math/yk_math.h>
#include <yk/rendering/yk_shader.h>
#include <yk/rendering/yk_texture.h>
#include <yk/data_structures/yk_yektor.h>
#include <yk/rendering/yk_color.h>

// For mario game, I will use this renderer. After learning vulkan, I will rewrite this
// and make it chad ish. But before that I will complete reading a couple C books I have
// been reading. I want to complete mario hiemer 9/10

// for a 2d renderer, only an ortho camera makes sense. if you want to do 3d stuff pr funky 2d stuff like
// perspective, then use a 3d camera/renderer. 8/30?


extern i4 draw_calls;


/*
Yes, I get it. But I need to understand the goals of the renderer better to want to make it more generic.
*/

typedef struct YK_Renderer2d
{
    /*
        Current camera2d reference. Cameras are "owned" by the app. The
        app creates them and the renderer can choose which camera to render
        to. Soon enough there will be a viewport to offload some duties to.
    */
    YK_Camera2d *current_cam;

    m4f view_mat;

    m4f proj_mat;

} YK_Renderer2d;

void yk_renderer2d_render_rect(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color* col);
void yk_renderer2d_render_rect_sprite(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color* col, YK_Texture *texture);
void yk_renderer2d_render_line(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color* col);

void yk_renderer2d_innit(YK_Renderer2d *renderer, YK_Camera2d *current_cam, YK_Window *win);
void yk_renderer2d_run(YK_Renderer2d *renderer, YK_Window *win);
void yk_renderer2d_cleanup();

void yk_renderer2d_set_bg(f4 r, f4 g, f4 b, f4 a);

#endif