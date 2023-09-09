#include <yk/yk_app.h>
#include <time.h>

#define num_babbit 10

#define POSITION_COMPONENT (1 << 0)
#define SPRITE_COMPONENT (1 << 1)
#define PLAYER_COMPONENT (1 << 2)

typedef struct YK_Player
{
  YK_Camera2d *cam;
} YK_Player;

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

YK_Yektor pos_comps;
YK_Yektor sprite_comps;
YK_Player py;

u1 comp_mask[num_babbit];

b1 has_component(int id, int type)
{
  return (comp_mask[id] & type) != 0;
}

void yk_ecs_sprite_render_system(YK_Renderer2d *ren)
{

  for (int i = 0; i < sprite_comps.size; i++)
  {
    // printf("%d %hhd %hhd \n", i, has_component(i, POSITION_COMPONENT), has_component(i, SPRITE_COMPONENT));
    if (has_component(i, POSITION_COMPONENT) && has_component(i, SPRITE_COMPONENT))
    {
      YK_Sprite *_sprite = (YK_Sprite *)yk_yektor_get(&sprite_comps, i);
      YK_Vec3f *_pos = (YK_Vec3f *)yk_yektor_get(&pos_comps, i);

      // printf("%f \n", _pos->z);

      // some reason, sprite data is lost. check how yektor stores shit.
      // texture data is lost only. So weird.

      yk_sprite_set_pos(_sprite, _pos);
      yk_renderer2d_render_sprite(ren, _sprite);
    }
  }
}

void yk_ecs_player_system(int player, f4 delta)
{
  if (has_component(player, POSITION_COMPONENT) && has_component(player, PLAYER_COMPONENT))
  {
    YK_Vec3f *_pos = (YK_Vec3f *)yk_yektor_get(&pos_comps, player);

    float speed = 5.f * delta;
    if (yk_input_is_key_held(YK_KEY_W))
    {
      _pos->y += speed;
    }

    if (yk_input_is_key_held(YK_KEY_A))
    {
      _pos->x -= speed;
    }

    if (yk_input_is_key_held(YK_KEY_S))
    {
      _pos->y -= speed;
    }

    if (yk_input_is_key_held(YK_KEY_D))
    {
      _pos->x += speed;
    }
  }
}

/*
Hall of fame -

&(*(YK_Vec3f *)yk_yektor_get(&pos_comps, i))
Although I am sure the compiler optimized something that meaningless away
*/

// need some kind of check array. get works exactly as it should, not as I hoped it could.
// But 10:30 is bed time and I am trying to be sane, so I will sleep.
// Did some reading and watched elvis the alien video. I need sparse sets for exactly this.
// still can't wrap around why I need sparse sets, and how SoA would be better for this.
// I could use a bitmask (or array of booleans for easier implementation) to decide if someone
// has a component. Maybe this will make sense later.
// I ended up using bitmasks

int main()
{

  YK_Window win;
  yk_window_innit(&win);
  yk_window_set_vsync(&win, false);

  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, &win);

  yk_yektor_innit(&pos_comps, 10, sizeof(YK_Vec3f));
  yk_yektor_innit(&sprite_comps, 10, sizeof(YK_Sprite));

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  int player = yk_ecs_create_entity();

  {
    YK_Sprite ps;
    yk_sprite_innit(&ps, "yk-res/textures/yk.png");
    yk_yektor_push(&sprite_comps, &ps);
  }

  {
    YK_Vec3f pos = {1.f, 0.f, -1.f};
    yk_yektor_push(&pos_comps, &pos);
  }

  {
    py.cam = &cam2d;
    yk_yektor_push(&pos_comps, &py);
  }

  comp_mask[player] = POSITION_COMPONENT | SPRITE_COMPONENT | PLAYER_COMPONENT;

  while (yk_window_is_running(&win))
  {

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    // debug_input(&cam2d, delta_time);

    yk_renderer2d_run(&ren2d, &win);

    yk_ecs_sprite_render_system(&ren2d);

    yk_ecs_player_system(player, delta_time);

    yk_window_run(&win);
  }

  yk_yektor_destroy(&pos_comps);
  yk_yektor_destroy(&sprite_comps);
  yk_window_destroy(&win);

  return 0;
}