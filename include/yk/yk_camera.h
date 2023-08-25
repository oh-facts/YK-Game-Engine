#ifndef YK_CAMERA_H
#define YK_CAMERA_H

#include <yk/math/yk_math.h>
#include <yk/yk_window.h>
#include <yk/yk_input.h>

typedef struct YK_Camera
{
    YK_Vec3f pos;
    YK_Vec3f front;
    YK_Vec3f up;
    f4 fov;
    b1 first_mouse;
    f4 yaw;
    f4 pitch;
    f4 lastX;
    f4 lastY;

} YK_Camera;

void yk_camera_innit(YK_Camera *camera);
void yk_camera_update(YK_Camera *camera, f4 delta_time);



#endif