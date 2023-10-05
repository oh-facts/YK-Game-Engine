#ifndef YK_CAMERA_H
#define YK_CAMERA_H

#include <yk/math/yk_math.h>
#include <yk/yk_window.h>
#include <yk/yk_input.h>
#include <yk/yk_defines.h>

#define YK_WORLD_UP (v3f){0.f,0.1f,0.f}

typedef enum YK_Camera_type
{
    YK_CAMERA_TYPE_P,
    YK_CAMERA_TYPE_O
} YK_Camera_type;

typedef struct YK_Camera
{
    v3f pos;
    v3f front;
    f4 fov;
    f4 yaw;
    f4 pitch;
    YK_Camera_type type;

} YK_Camera;


void yk_camera_innit(YK_Camera *camera,YK_Camera_type type);
void yk_camera_update(YK_Camera *camera, f4 delta_time);



#endif