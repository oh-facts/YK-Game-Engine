#include <yk/yk_app.h>
#include <time.h>

void debug_input(YK_Camera2d *cam, float delta)
{
  float speed = 5.f * delta;
  if (yk_input_is_key_held(YK_KEY_W))
  {
    yk_camera2d_move_up(cam, speed);
  }

  if (yk_input_is_key_held(YK_KEY_A))
  {
    yk_camera2d_move_left(cam, speed);
  }

  if (yk_input_is_key_held(YK_KEY_S))
  {
    yk_camera2d_move_down(cam, speed);
  }

  if (yk_input_is_key_held(YK_KEY_D))
  {
    yk_camera2d_move_right(cam, speed);
  }
}

/*
  To Do: 1. Rotations
         2. Unit Testing api
         3. Logger
*/
typedef struct YK_Position_component
{
  YK_Vec3f pos;
} YK_Position_component;

typedef struct YK_Sprite_component
{
  YK_Sprite sprite;
} YK_Sprite_component;

YK_Yektor *pos_comps;
YK_Yektor *sprite_comps;

i4 *entity_list;

void yk_ecs_gravity_system(f4 delta)
{
  for (int i = 0; i < pos_comps->size; i++)
  {
    (*(YK_Position_component *)yk_yektor_at(pos_comps, i)).pos.y -= delta;
  }
}

void yk_ecs_sprite_render_system(YK_Renderer2d *ren)
{

  for (int i = 0; i < sprite_comps->size; i++)
  {
    YK_Sprite *_sprite = &(*(YK_Sprite_component *)yk_yektor_at(sprite_comps, i)).sprite;
    YK_Vec3f *_pos = &(*(YK_Position_component *)yk_yektor_at(pos_comps, i)).pos;

    yk_sprite_set_pos(_sprite, _pos);
    yk_renderer2d_render_sprite(ren, _sprite);
  }
}

int main()
{

  YK_Window win;
  yk_window_innit(&win);

  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, &win);

  int babbit1 = yk_ecs_create_entity();

  pos_comps = yk_yektor_innit(1, sizeof(YK_Position_component));
  sprite_comps = yk_yektor_innit(1, sizeof(YK_Sprite_component));
  YK_Position_component pos1;
  pos1.pos.x = 0.5f;
  pos1.pos.y = 0.5f;
  pos1.pos.z = -1.f;

  YK_Sprite_component sp1;
  YK_Sprite _a = yk_sprite_create("yk-res/textures/default.jpg");
  sp1.sprite = _a;
  yk_sprite_set_pos(&sp1.sprite, &(YK_Vec3f){0.f, 0.f, -1.f});
  yk_yektor_push(pos_comps, &pos1);
  yk_yektor_push(sprite_comps, &sp1);

  YK_Position_component x = *(YK_Position_component *)yk_yektor_at(pos_comps, 0);

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  YK_Sprite babbits[20];

  srand(time(NULL));

  /*
    for (int i = 0; i < 10; i++)
    {
      babbits[i] = yk_sprite_create("yk-res/textures/default.jpg");
      float rx = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
      float ry = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
      float rz = ((float)rand() / RAND_MAX) * -10.0f;
      yk_sprite_set_pos(&babbits[i], &(YK_Vec3f){rx, ry, -1.f});
    }
  */

  for (int i = 0; i < 10; i++)
  {
  }

  while (yk_window_is_running(&win))
  {

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    yk_camera2d_update(&cam2d, delta_time);
    debug_input(&cam2d, delta_time);

    yk_renderer2d_run(&ren2d, &win);
    /*
    for (int i = 0; i < 10; i++)
    {
      yk_renderer2d_render_sprite(&ren2d, &babbits[i]);
    }
*/

    yk_ecs_sprite_render_system(&ren2d);

    yk_ecs_gravity_system(delta_time);

    yk_window_run(&win);
  }


  return 0;
}