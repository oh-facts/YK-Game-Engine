#include <yk/yk_app.h>

struct player
{
    YK_Vec2f rb_pos;
    YK_Sprite sp;
};

typedef struct player player;

#define SPEED 4
void update_player(player *py)
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

    yk_rigidbody_set_vel(0, &mv);
    YK_Vec2f pos = yk_rigidbody_get_pos(0);
    py->sp.transform.pos.x = pos.x;
    py->sp.transform.pos.y = pos.y;
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

    player py = {.rb_pos = {0,0}};
    yk_rigidbody_add_(&py.rb_pos, 1.f);
    yk_sprite_innit(&py.sp, "yk-res/textures/yk.png");

    

    while (yk_window_is_running(&win))
    {

        f4 current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // debug_input(&cam2d, delta_time);

        update_player(&py);
        yk_physics_update(delta_time);

        yk_renderer2d_run(&ren2d, &win);
        yk_renderer2d_render_sprite(&ren2d, &py.sp);


        yk_window_run(&win);
    }

    return 0;
}