#include <yk/yk_camera2d.h>

void yk_camera2d_innit(YK_Camera2d *camera)
{
    yk_vec3f_mem_set(&camera->front, 0.f);
    camera->front.z = -1.f;

    yk_vec3f_mem_set(&camera->pos, 0.f);

    camera->zoom = 1.f;
}

void yk_camera2d_set_pos2d(YK_Camera2d *camera, YK_Vec3f *pos)
{
    //idk if dereferenceing is faster than copying
    //ofc, setting directly is much better than using a setter
    camera->pos.x = pos->x;
    camera->pos.y = pos->y;
    
}

void yk_camera2d_update(YK_Camera2d *camera, f4 delta_time)
{
    // printf("%f\n",camera->pos.y);
}

YK_Mat4f yk_camera2d_get_projection_matrix(YK_Camera2d *camera, f4 aspect_ratio)
{
    // return yk_mat4f_perspective(45.f * DEG_TO_RAD, 1.f, 0.1f, 100.f);
    f4 zoom = camera->zoom;
    return yk_mat4f_ortho(-aspect_ratio * zoom, aspect_ratio * zoom, -zoom, zoom, 2.f, 100.f);
}

YK_Mat4f yk_camera2d_get_view_matrix(YK_Camera2d *camera)
{

    YK_Vec3f _temp = yk_math_vec3f_add(&camera->pos, &YK_WORLD_FORWARD);
    return yk_look_at(&camera->pos, &_temp, &YK_WORLD_UP);
}

void yk_camera2d_move_up(YK_Camera2d *camera, f4 distance)
{
    YK_Vec3f _temp = yk_math_vec3f_mul_s(&YK_WORLD_UP, distance);
    camera->pos = yk_math_vec3f_add(&camera->pos, &_temp);
}

void yk_camera2d_move_left(YK_Camera2d *camera, f4 distance)
{
    YK_Vec3f _temp = yk_math_vec3f_mul_s(&YK_WORLD_LEFT, distance);
    camera->pos = yk_math_vec3f_add(&camera->pos, &_temp);
}

void yk_camera2d_move_right(YK_Camera2d *camera, f4 distance)
{
    YK_Vec3f _temp = yk_math_vec3f_mul_s(&YK_WORLD_RIGHT, distance);
    camera->pos = yk_math_vec3f_add(&camera->pos, &_temp);
}

void yk_camera2d_move_down(YK_Camera2d *camera, f4 distance)
{
    YK_Vec3f _temp = yk_math_vec3f_mul_s(&YK_WORLD_DOWN, distance);
    camera->pos = yk_math_vec3f_add(&camera->pos, &_temp);
}