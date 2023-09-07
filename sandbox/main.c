#include <yk/yk_app.h>
#include <time.h>

#define num_babbit 10

#define POSITION_COMPONENT (1 << 0)
#define GRAVITY_COMPONENT (1 << 1)
#define JUMP_COMPONENT (1 << 2)

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
YK_Yektor jump_comps;

u1 comp_mask[num_babbit];

b1 has_component(int id, int type)
{
  return (comp_mask[id] & type) != 0;
}

typedef struct YK_Jump_component
{
  int jump;
} YK_Jump_component;

void yk_ecs_gravity_system(f4 delta)
{
  for (int i = 0; i < pos_comps.size; i++)
  {
    (*(YK_Vec3f *)yk_yektor_get(&pos_comps, i)).y -= delta;
  }
}

void yk_ecs_sprite_render_system(YK_Renderer2d *ren)
{

  for (int i = 0; i < sprite_comps.size; i++)
  {
    YK_Sprite *_sprite = &(*(YK_Sprite *)yk_yektor_get(&sprite_comps, i));
    YK_Vec3f *_pos = &(*(YK_Vec3f *)yk_yektor_get(&pos_comps, i));

    yk_sprite_set_pos(_sprite, _pos);
    yk_renderer2d_render_sprite(ren, _sprite);
  }
}

void yk_ecs_jump(f4 delta)
{
  for (int i = 0; i < pos_comps.size; i++)
  {
    if (has_component(i, JUMP_COMPONENT))
    {
      if (yk_input_is_key_tapped(YK_KEY_SPACE))
      {
        YK_Jump_component *_jump = ((YK_Jump_component *)yk_yektor_get(&jump_comps, i));
        (*(YK_Vec3f *)yk_yektor_get(&pos_comps, i)).y += 0.5f * _jump->jump;
      }
    }
  }
}

// need some kind of check array. get works exactly as it should, not as I hoped it could.
// But 10:30 is bed time and I am trying to be sane, so I will sleep.
// Did some reading and watched elvis the alien video. I need sparse sets for exactly this.
// still can't wrap around why I need sparse sets, and how SoA would be better for this.
// I could use a bitmask (or array of booleans for easier implementation) to decide if someone
// has a component. Maybe this will make sense later.
//I ended up using bitmasks

int main()
{

  YK_Window win;
  yk_window_innit(&win);
  yk_window_set_vsync(&win, false);

  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, &win);

  int babbits[num_babbit];
  yk_yektor_innit(&pos_comps, num_babbit, sizeof(YK_Vec3f));
  yk_yektor_innit(&sprite_comps, num_babbit, sizeof(YK_Sprite));
  yk_yektor_innit(&jump_comps, num_babbit, sizeof(YK_Jump_component));

  srand(time(NULL));

  for (int i = 0; i < num_babbit; i++)
  {
    babbits[i] = yk_ecs_create_entity();
    float rx = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
    float ry = ((float)rand() / RAND_MAX) * 5.f - 2.5f;

    YK_Vec3f _vec3f;
    _vec3f.x = rx;
    _vec3f.y = ry;
    _vec3f.z = -1.f;

    yk_yektor_push(&pos_comps, &_vec3f);

    /*
    What the fuck is this

    YK_Sprite _sprite = *(YK_Sprite *)malloc(sizeof(YK_Sprite));
    */

    YK_Sprite _sprite;
    yk_sprite_innit(&_sprite, "yk-res/textures/default.jpg");
    yk_sprite_set_pos(&_sprite, &(YK_Vec3f){0.f, 0.f, -1.f});
    yk_yektor_push(&sprite_comps, &_sprite);



    if (i % 2 == 0)
    {
      YK_Jump_component _jump;
      _jump.jump = 2;
      yk_yektor_set(&jump_comps, &_jump, i);
      comp_mask[i] = JUMP_COMPONENT;
      printf("%d", i);
    }
  }

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  while (yk_window_is_running(&win))
  {

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    yk_camera2d_update(&cam2d, delta_time);
    debug_input(&cam2d, delta_time);

    yk_renderer2d_run(&ren2d, &win);

    yk_ecs_sprite_render_system(&ren2d);

    yk_ecs_gravity_system(delta_time);
    yk_ecs_jump(delta_time);

    yk_window_run(&win);
  }

  yk_yektor_destroy(&pos_comps);
  yk_yektor_destroy(&sprite_comps);
  yk_window_destroy(&win);

  return 0;
}