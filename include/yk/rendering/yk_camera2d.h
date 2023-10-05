#ifndef YK_CAMERA2D_H
#define YK_CAMERA2D_H

#include <yk/math/yk_math.h>
#include <yk/yk_window.h>
#include <yk/yk_input.h>
#include <yk/yk_defines.h>


#define YK_WORLD_UP (v3f){0.f,1.f,0.f}
#define YK_WORLD_LEFT (v3f){-1.f,0.f,0.f}
#define YK_WORLD_RIGHT (v3f){1.f,0.f,0.f}
#define YK_WORLD_DOWN (v3f){0.f,-1.f,0.f}
#define YK_WORLD_FORWARD (v3f){0.f,0.f,-1.f}
#define YK_WORLD_BACKWARD (v3f){0.f,0.f,1.f}

/*
  Orthographic 2d camera.
  Meant to be used with the renderer2d.
*/
typedef struct YK_Camera2d
{
    v3f pos;
    v3f front;
    f4 zoom;

} YK_Camera2d;

void yk_camera2d_innit(YK_Camera2d *camera);
void yk_camera2d_update(YK_Camera2d *camera, f4 delta_time);

m4f yk_camera2d_get_projection_matrix(YK_Camera2d *camera, f4 aspect_ratio);
m4f yk_camera2d_get_view_matrix(YK_Camera2d *camera);

void yk_camera2d_set_pos2d(YK_Camera2d *camera, v3f *pos);

void yk_camera2d_move_up(YK_Camera2d *camera, f4 distance);
void yk_camera2d_move_left(YK_Camera2d *camera, f4 distance);
void yk_camera2d_move_right(YK_Camera2d *camera, f4 distance);
void yk_camera2d_move_down(YK_Camera2d *camera, f4 distance);



#endif