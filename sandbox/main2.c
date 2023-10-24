#include "yk/math/yk_math_types.h"
#include "yk/physics/yk_physics.h"
#include <yk/yk_app.h>

struct entity
{
    YK_Transform2d transform;
    YK_Particle2d *particle;
};

typedef struct entity entity;

YK_Particle2d *super_mega_cunt;

#define SPEED 4
void update_player(entity *py, f4 delta, /*debug purposes*/ YK_Renderer2d *ren)
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

    if (yk_input_is_key_held(YK_KEY_SPACE))
    {
        v2f _pos = yk_aabb_get_pos(&py->particle->collider.collision_shape.aabb);
        //_pos.y -= 1.f;
        v2f _dir = {0.f, -1.f};
        // yk_vec2f_print(&_pos);
        b1 hit = yk_physics_aabb_raycast(&super_mega_cunt->collider.collision_shape.aabb, _pos, _dir, 0.5f);
        yk_renderer2d_render_line_o(ren, _pos, _dir, 0.5f, 0.05f, &YK_COLOR_ORANGE);

        printf("%d", hit);
    }

    py->particle->vel = mv;
    py->transform.pos = py->particle->pos;
}

int main()
{
    YK_Window *win = yk_window_create_default();

    yk_window_set_vsync(win, false);

    YK_Camera2d cam2d;
    yk_camera2d_innit(&cam2d);
    cam2d.zoom = 1.f;

    YK_Renderer2d ren2d;
    yk_renderer2d_innit(&ren2d, &cam2d, win);

    f4 delta_time = 0.f;
    f4 last_frame = 0.f;

    yk_renderer2d_set_bg(0.07f, 0.13f, 0.17f, 1.f);

    YK_Texture test = yk_texture_create("yk-res/textures/yk.png");
    yk_physics_innit();

    entity py = {.transform = {{-1.f, 0}, 0, {1.f, 1.f}}};
    {
        py.particle = yk_particles_create((v2f){-1.f, 0}, 0.f, 1.f);
        py.particle->debug_draw = true;
        py.particle->static_object = false;
        yk_particle_set_aabb(py.particle, (v2f){0, -0.4f}, (v2f){0.5f, 0.2f});
        py.particle->gravity = 1.f;
    }

    {
        super_mega_cunt = yk_particles_create((v2f){-1.f, -1.f}, 0.f, 1.f);
        super_mega_cunt->debug_draw = true;
        super_mega_cunt->static_object = true;
        yk_particle_set_aabb(super_mega_cunt, (v2f){0.f, 0.f}, (v2f){0.2f, 0.1f});
    }

    entity testo = {.transform = {{1.f, 0.f}, 0, {1.f, 1.f}}};
    {
        testo.particle = yk_particles_create((v2f){1.f, 0.f}, 0.f, 1.f);
        testo.particle->debug_draw = true;
        testo.particle->static_object = true;
        yk_particle_set_aabb(testo.particle, (v2f){0.f, 0.f}, testo.transform.scale);
    }

    // yk_particle_set_aabb(py.particle, (v2f){0,0}, (v2f){1.f,1.f});

    v2f *pos = &py.transform.pos;
    f4 rot = 0 * DEG_TO_RAD;
    v2f scale = {.x = 1, .y = 0.1f};

    YK_Color moop = {77, 77, 256, 256};
    NORMALIZE_RGBA(moop);

    // py.particle->vel.x = 0.2f;

    while (yk_window_is_running(win))
    {

        f4 current_frame = yk_get_time();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // debug_input(&cam2d, delta_time);

        yk_particle_integrate(delta_time);

        yk_renderer2d_begin_draw(&ren2d, win);
        update_player(&py, delta_time, &ren2d);

        yk_renderer2d_render_rect(&ren2d, &py.transform, 0.01f, &YK_COLOR_CYAN);

        yk_renderer2d_render_line_o(&ren2d, V2F_ZERO, (v2f){1, 1}, 0.4f, 0.05f, &YK_COLOR_GREEN);
        yk_renderer2d_render_line_p(&ren2d, yk_math_vec2f_add(&py.transform.pos, &(v2f){1.f, 1.f}), current_frame, 0.05f, &YK_COLOR_MAGENTA);
        yk_renderer2d_render_line(&ren2d, &(YK_Transform2d){.pos = *pos, .rot_z = rot, .scale = scale}, &YK_COLOR_MAGENTA);

        yk_renderer2d_render_quad_sprite(&ren2d, &py.transform, &YK_COLOR_WHITE, &test);
        yk_renderer2d_render_quad_sprite(&ren2d, &testo.transform, &moop, &test);

        yk_particle_collison_shape_debug_draw(&ren2d);

        // printf("Draw Calls: %d\n",draw_calls);

        yk_window_update(win);
    }

    yk_renderer2d_destroy();
    yk_window_destroy(win);

    return 0;
}
