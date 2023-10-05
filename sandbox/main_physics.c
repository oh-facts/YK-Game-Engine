#include <yk/yk_app.h>

// store data owner by others a pointer you twat (4:54am 9/27)
// What was I trying to say? (4:11pm 9/27)
struct entity
{
    i4 id;
    YK_Transform transform;
    YK_Aabb aabb;
};

typedef struct entity entity;

#define SPEED 5
#define JUMP_FORCE ((v2f){0.f, 800.f})
void update_player(entity *py)
{
    v2f mv = {0, 0};

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
        v2f acc = ((YK_Rigidbody *)yk_yektor_get(&yk_rigidbodies, py->id))->acceleration;
    }

    yk_rigidbody_set_vel(py->id, &mv);
    v2f pos = yk_rigidbody_get_pos(py->id);
    py->transform.pos.x = pos.x;
    py->transform.pos.y = pos.y;
    // printf("%f\n",py->transform.pos.x);
}

#define GRAVITY ((YK_Vec2f){0.f, -9.8f})

void gravity(int id)
{
    // yk_rigidbody_add_force(id, &GRAVITY);
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

    entity py = {.transform = {{0, 0, -2.f}, {0, 0, 0}, {1.f, 1.f, 0}}, .id = 0};

    yk_rigidbody_add_(&(v2f){py.transform.pos.x, py.transform.pos.y}, 1.f);
    py.aabb.pos.x = py.transform.pos.x;
    py.aabb.pos.y = py.transform.pos.y;
    py.aabb.size.x = py.transform.scale.x;
    py.aabb.size.y = py.transform.scale.y;

    entity floor = {.transform = {{0, -2.f, -2.f}, {0, 0, 0}, {5.f, 1.f, 0}}, .id = 1};
    yk_rigidbody_add_(&(v2f){floor.transform.pos.x, floor.transform.pos.y}, 1.f);

    YK_Texture outline = yk_texture_create("yk-res/textures/outline.png");

    //  yk_window_set_vsync(&win, true);

    while (yk_window_is_running(&win))
    {

        f4 current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        update_player(&py);
        gravity(py.id);

        yk_physics_update(delta_time);

        // debug_input(&cam2d, delta_time);

        yk_renderer2d_run(&ren2d, &win);

        // yk_renderer2d_render_rect(&ren2d, &py.transform, &YK_COLOR_WHITE);
        yk_renderer2d_render_rect(&ren2d, &floor.transform, &YK_COLOR_WHITE);
        yk_renderer2d_render_rect_sprite(&ren2d, &py.transform, &YK_COLOR_WHITE, &outline);

        // printf("draw calls: %d \n", draw_calls);

        yk_window_run(&win);
    }

    return 0;
}