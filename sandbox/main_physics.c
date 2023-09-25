#include <yk/yk_app.h>

#define NUM 100

struct entity
{
    YK_Transform transform;
    YK_Rect sp;
};

typedef struct entity entity;

#define SPEED 4
#define JUMP_FORCE ((YK_Vec2f){0.f, 5000.f})
void update_player(entity *py)
{
    YK_Vec2f mv = {0, 0};

    if (yk_input_is_key_held(YK_KEY_W))
    {
        mv.y = SPEED;
    }

    if (yk_input_is_key_held(YK_KEY_A))
    {
        mv.x = -SPEED;
    }

    if (yk_input_is_key_held(YK_KEY_S))
    {
        mv.y = -SPEED;
    }

    if (yk_input_is_key_held(YK_KEY_D))
    {
        mv.x = SPEED;
    }
    if (yk_input_is_key_tapped(YK_KEY_SPACE))
    {
        yk_rigidbody_add_force(0, &JUMP_FORCE);
        YK_Vec2f acc = ((YK_Rigidbody *)yk_yektor_get(&yk_rigidbodies,0))->acceleration;
        yk_vec2f_print(&acc);
    }

    yk_rigidbody_set_vel(0, &mv);
    YK_Vec2f pos = yk_rigidbody_get_pos(0);
    py->transform.pos.x = pos.x;
    py->transform.pos.y = pos.y;
    // printf("%f\n",py->transform.pos.x);
}

int main()
{
    YK_Window win;
    yk_window_innit(&win);
    yk_window_set_vsync(&win, false);

    YK_Camera2d cam2d;
    yk_camera2d_innit(&cam2d);
    cam2d.zoom = 2.f;

    YK_Renderer2d ren2d;
    yk_renderer2d_innit(&ren2d, &cam2d, &win);

    f4 delta_time = 0.f;
    f4 last_frame = 0.f;

    yk_renderer2d_set_bg(0.2f, 0.3f, 0.3f, 1.f);

    yk_physics_innit();

    entity py = {.transform = {{0, 0, -2.f}, {0, 0, 0}, {1.f, 1.f, 0}}};

    yk_rigidbody_add_(&(YK_Vec2f){py.transform.pos.x, py.transform.pos.y}, 1.f);

    yk_rect_innit(&py.sp);

    while (yk_window_is_running(&win))
    {

        f4 current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // debug_input(&cam2d, delta_time);

        update_player(&py);
        yk_physics_update(delta_time);

        yk_renderer2d_run(&ren2d, &win);
        yk_renderer2d_render_rect(&ren2d, &py.transform, &YK_COLOR_WHITE);

        //printf("draw calls: %d \n", draw_calls);

        yk_window_run(&win);
    }

    return 0;
}