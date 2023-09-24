#include <yk/yk_app.h>

struct player
{
    YK_Transform transform;
};

typedef struct player player;

#define SPEED 4
void update_player(player *py, f4 delta)
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

    py->transform.pos.x += mv.x * delta;
    py->transform.pos.y += mv.y * delta;
}

int main()
{
    YK_Window win;
    yk_window_innit(&win);
    yk_window_set_vsync(&win, false);

    YK_Camera2d cam2d;
    yk_camera2d_innit(&cam2d);
    cam2d.zoom = 1.f;

    YK_Renderer2d ren2d;
    yk_renderer2d_innit(&ren2d, &cam2d, &win);

    f4 delta_time = 0.f;
    f4 last_frame = 0.f;

    yk_renderer2d_set_bg(0.2f, 0.3f, 0.3f, 1.f);

    yk_physics_innit();

    player py = {.transform={{0, 0, -2.f}, {0, 0, 0}, {1.f, 1.f, 0}}} ;
    
    YK_Rect rect;
    yk_rect_innit(&rect);


    while (yk_window_is_running(&win))
    {

        f4 current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // debug_input(&cam2d, delta_time);

        update_player(&py,delta_time);
        yk_physics_update(delta_time);

        yk_renderer2d_run(&ren2d, &win);
        yk_renderer2d_render_rect(&ren2d,&rect,&py.transform);

        //printf("%f \n",py.transform.pos.x);

        yk_window_run(&win);
    }

    return 0;
}