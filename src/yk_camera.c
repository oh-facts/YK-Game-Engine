#include <yk/yk_camera.h>
#include <yk/yk_input.h>

void _camera_mouse_movement(YK_Camera *camera);
void _camera_mouse_scroll(YK_Camera *camera);
void _camera_keyboard(YK_Camera *camera, f4 delta_time);

void yk_camera_innit(YK_Camera *camera)
{
    camera->pos.x = 0.0f;
    camera->pos.y = 0.0f;
    camera->pos.z = 3.0f;

    camera->front.x = 0.0f;
    camera->front.y = 0.0f;
    camera->front.z = -1.0f;

    camera->up.x = 0.0f;
    camera->up.y = 1.0f;
    camera->up.z = 0.0f;

    camera->fov = 45.0f;
    camera->first_mouse = true;
    camera->yaw = -90.0f;
    camera->pitch = 0.0f;
    camera->lastX = WIDTH / 2;
    camera->lastY = HEIGHT / 2;
}

void yk_camera_update(YK_Camera *camera, f4 delta_time)
{
    _camera_mouse_movement(camera);
    _camera_mouse_scroll(camera);
    _camera_keyboard(camera, delta_time);
}

/*
    Internal helper function used in camera update
*/
void _camera_mouse_movement(YK_Camera *camera)
{

    f4 xpos = yk_input_mouse_position.x;
    f4 ypos = yk_input_mouse_position.y;

    if (camera->first_mouse)
    {
        camera->lastX = xpos;
        camera->lastY = ypos;
        camera->first_mouse = false;
    }

    f4 xoffset = xpos - camera->lastX;
    f4 yoffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;

    f4 sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->yaw += xoffset;
    camera->pitch += yoffset;

    if (camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if (camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    YK_Vec3f front;
    front.x = -cos(camera->yaw * DEG_TO_RAD) * cos(camera->pitch * DEG_TO_RAD);
    front.y = sin(camera->pitch * DEG_TO_RAD);
    front.z = sin(camera->yaw * DEG_TO_RAD) * cos(camera->pitch * DEG_TO_RAD);

    camera->front = yk_vec3f_normalize(&front);
}

/*
    Internal helper function used in camera update
*/
void _camera_mouse_scroll(YK_Camera *camera)
{
    camera->fov -= yk_input_mouse_scroll;   
    if (camera->fov < 1.0f)
        camera->fov = 1.0f;
    if (camera->fov > 45.0f)
        camera->fov = 45.0f;
    
    printf("%f \n", camera->fov);
}

void _camera_keyboard(YK_Camera *camera, f4 delta_time)
{
    float cameraSpeed = 2.5f * delta_time;
    if (yk_input_is_key_held(YK_KEY_W))
    {
        YK_Vec3f temp = yk_math_vec3f_mul_s(&camera->front, cameraSpeed);
        camera->pos = yk_math_vec3f_add(&camera->pos, &temp);
    }
    if (yk_input_is_key_held(YK_KEY_S))
    {
        YK_Vec3f temp = yk_math_vec3f_mul_s(&camera->front, cameraSpeed);
        camera->pos = yk_math_vec3f_sub(&camera->pos, &temp);
    }
    if (yk_input_is_key_held(YK_KEY_D))
    {
        YK_Vec3f temp = yk_math_vec3f_cross(&camera->front, &camera->up);
        YK_Vec3f temp2 = yk_vec3f_normalize(&temp);
        YK_Vec3f temp3 = yk_math_vec3f_mul_s(&temp2, cameraSpeed);
        camera->pos = yk_math_vec3f_sub(&camera->pos, &temp3);
    }
    if (yk_input_is_key_held(YK_KEY_A))
    {
        YK_Vec3f temp = yk_math_vec3f_cross(&camera->front, &camera->up);
        YK_Vec3f temp2 = yk_vec3f_normalize(&temp);
        YK_Vec3f temp3 = yk_math_vec3f_mul_s(&temp2, cameraSpeed);
        camera->pos = yk_math_vec3f_add(&camera->pos, &temp3);
    }
}