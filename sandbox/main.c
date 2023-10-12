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
  YK_Window win;
  yk_window_innit(&win);
  yk_window_set_vsync(&win, false);

  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);
  cam2d.zoom = 3.f;

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, &win);

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  yk_renderer2d_set_bg(0.2f, 0.3f, 0.3f, 1.f);

  entity py = {.transform = {{0, 0}, 0, {2.f, 2.f}}};

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

  while (yk_window_is_running(&win))
  {

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    // debug_input(&cam2d, delta_time);

    update_player(&py, delta_time);

    yk_renderer2d_run(&ren2d, &win);
    yk_renderer2d_render_rect_sprite(&ren2d, &py.transform, &YK_COLOR_WHITE, &test2);

    for (int i = 0; i < NUM; i++)
    {
      f4 timeValue = (glfwGetTime() + i * 0.1f) * SIM_SPEED;
      f4 r = sin(timeValue) / 2.0f + 0.5f;
      f4 g = sin(timeValue + 2.0f) / 2.0f + 0.5f;
      f4 b = sin(timeValue + 4.0f) / 2.0f + 0.5f;

      squares[i].transform.rot_z = timeValue * ROT_SPEED;
      yk_renderer2d_render_rect(&ren2d, &squares[i].transform, &(YK_Color){r, g, b, 1.f});
    }

    // printf("Draw Calls: %d\n",draw_calls);

    yk_window_run(&win);
  }

  yk_renderer2d_cleanup();
  yk_window_destroy(&win);

  return 0;
}