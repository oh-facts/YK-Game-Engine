#include <yk/yk_app.h>

#define NUM (1000)

#define SIM_SPEED (5.f)
#define ROT_SPEED (5.0f)

struct entity
{
  YK_Transform2d transform;
};

typedef struct entity entity;

#define SPEED 4
void update_player(entity *py, f4 delta)
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

  py->transform.pos.x += mv.x * delta;
  py->transform.pos.y += mv.y * delta;
}

int main()
{
  // YK_Window *win = yk_window_create("this is a title", 960, 540);
  YK_Window *win = yk_window_create_default();
  yk_window_set_vsync(win, false);

  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);
  cam2d.zoom = 0.5f;

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, win);

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  yk_renderer2d_set_bg(0.2f, 0.3f, 0.3f, 1.f);

  entity py = {.transform = {{0, 0}, 0, {1.f, 1.f}}};

  yk_renderer2d_set_bg(0.5f, 0.2f, 0.4f, 1.f);

  entity squares[NUM];
  for (int i = 0; i < NUM; i++)
  {
    f4 r1_x = ((f4)rand() / RAND_MAX) * 20.0f - 10.f;
    f4 r1_y = ((f4)rand() / RAND_MAX) * 10.0f - 5.f;
    f4 r2 = ((f4)rand() / RAND_MAX) * 90.0f;
    f4 r3 = ((f4)rand() / RAND_MAX) * 0.5f + 0.2f;
    YK_Transform2d trans = {{r1_x, r1_y}, r2, {r3, r3}};

    squares[i].transform = trans;
  }

  YK_Texture test = yk_texture_create("yk-res/textures/yk.png");
  YK_Texture test2 = yk_texture_create("yk-res/textures/default.jpg");

  while (yk_window_is_running(win))
  {

    f4 current_frame = yk_get_time();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    // debug_input(&cam2d, delta_time);

    update_player(&py, delta_time);

    yk_renderer2d_begin_draw(&ren2d, win);
    yk_renderer2d_render_quad_sprite_z(&ren2d, &py.transform, -8.f, &YK_COLOR_WHITE, &test2);

    for (int i = 0; i < NUM; i++)
    {
      f4 timeValue = (yk_get_time() + i * 0.1f) * SIM_SPEED;
      f4 r = sin(timeValue) / 2.0f + 0.5f;
      f4 g = sin(timeValue + 2.0f) / 2.0f + 0.5f;
      f4 b = sin(timeValue + 4.0f) / 2.0f + 0.5f;

      squares[i].transform.rot_z = timeValue * ROT_SPEED;
      yk_renderer2d_render_quad_z(&ren2d, &squares[i].transform, -9.f, &(YK_Color){r, g, b, 1.f});
    }

    // printf("Draw Calls: %d\n",draw_calls);

    yk_window_update(win);
  }

  yk_renderer2d_destroy();
  yk_window_destroy(win);

  return 0;
}