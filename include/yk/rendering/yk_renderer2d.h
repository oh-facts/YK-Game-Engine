#ifndef YK_RENDERER2D_H
#define YK_RENDERER2D_H


#include <yk/rendering/yk_camera2d.h>
#include <yk/math/yk_math.h>
#include <yk/rendering/yk_shader.h>
#include <yk/rendering/yk_texture.h>
#include <yk/data_structures/yk_yektor.h>
#include <yk/rendering/yk_color.h>

// for a 2d renderer, only an ortho camera makes sense. if you want to do 3d stuff pr funky 2d stuff like
// perspective, then use a 3d camera/renderer. 8/30?

extern i4 draw_calls;

typedef struct YK_Renderer2d
{
    /*
        Current camera2d reference. Cameras are "owned" by the creator.
        The renderer can choose which camera to render
        to. Soon enough there will be a viewport to offload some duties to.
    */
    YK_Camera2d *current_cam;

    m4f view_mat;

    m4f proj_mat;

} YK_Renderer2d;

/*
    Renders a quad. A quad is a filled rectangle
*/
void yk_renderer2d_render_quad(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color *col);

/*
    Renders a quad at layer z. A quad is a filled rectangle
*/
void yk_renderer2d_render_quad_z(YK_Renderer2d *renderer, YK_Transform2d *transform, f4 layer, YK_Color *col);

/*
    Renders a sprite on a quad.
*/
void yk_renderer2d_render_quad_sprite(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color *col, YK_Texture *texture);

/*
    Renders a sprite at layer z on a quad.
*/
void yk_renderer2d_render_quad_sprite_z(YK_Renderer2d *renderer, YK_Transform2d *transform, f4 layer, YK_Color *col, YK_Texture *texture);

/*
    Renders a line at transform
*/
void yk_renderer2d_render_line(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color *col);

/*
    Renders a line with midpoint at pos.
*/
void yk_renderer2d_render_line_p(YK_Renderer2d *renderer, v2f pos, f4 rot, f4 thickness, YK_Color *col);

/*
    Renders a line starting at origin of length length and direction dir.
*/
void yk_renderer2d_render_line_o(YK_Renderer2d *renderer, v2f origin, v2f dir, f4 length, f4 thickness, YK_Color *col);

/*
    Renders a rect. A rect is an outlined rectangle.
*/
void yk_renderer2d_render_rect(YK_Renderer2d *renderer, YK_Transform2d *transform, f4 thickness, YK_Color *col);

/*
    Initializes a renderer
*/
void yk_renderer2d_innit(YK_Renderer2d *renderer, YK_Camera2d *current_cam, YK_Window *win);

/*
    Must be called before issuing draw calls
*/
void yk_renderer2d_begin_draw(YK_Renderer2d *renderer, YK_Window *win);

/*
    Destory renderer
*/
void yk_renderer2d_destroy();

/*
    Sets renderer background
*/
void yk_renderer2d_set_bg(f4 r, f4 g, f4 b, f4 a);

#endif