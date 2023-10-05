#include <yk/yk_app.h>
#include <time.h>

#define num_babbit 3

#define POSITION_COMPONENT (1 << 0)
#define SPRITE_COMPONENT (1 << 1)
#define PLAYER_COMPONENT (1 << 2)
#define COLLIDER_COMPONENT (1 << 3)

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
YK_Yektor aabb_comps;
YK_Player py;

u1 comp_mask[num_babbit];

b1 has_component(int id, int type)
{
  return (comp_mask[id] & type) != 0;
}

void yk_ecs_sprite_render_system(YK_Renderer2d *ren)
{

  for (int i = 0; i < num_babbit; i++)
  {
    // printf("%d %hhd %hhd \n", i, has_component(i, POSITION_COMPONENT), has_component(i, SPRITE_COMPONENT));
    if (has_component(i, POSITION_COMPONENT) && has_component(i, SPRITE_COMPONENT))
    {
      YK_Sprite *_sprite = yk_yektor_get(&sprite_comps, i);
      YK_Vec3f *_pos = yk_yektor_get(&pos_comps, i);

      // printf(" %d %f %d \n", i, _pos->x, _sprite->texture.width);

      // some reason, sprite data is lost. check how yektor stores shit.
      // texture data is lost only. So weird. Fixed that. I was initializing
      // my vectors incorrectly so there was no space for texture data
      // so everything but that was stored. New problem, for some reason, my
      // first texture is renderered on my second sprite, my second texture on my third
      // sprite and my third texture on my first sprite. Since I have only been ever
      // rendering the same thing I haven't noticed before maybe. Also, apparently,
      // I don't need to cast my void pointer to requried types. who knew.

      _sprite->transform.pos = *_pos;
      yk_renderer2d_render_sprite(ren, _sprite);
    }
  }
  // printf("\n");
}

void yk_ecs_player_system(int player, f4 delta)
{
  if (has_component(player, POSITION_COMPONENT) && has_component(player, PLAYER_COMPONENT))
  {
    YK_Vec3f *_pos = yk_yektor_get(&pos_comps, player);

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

void yk_ecs_physics_system(YK_Renderer2d *ren, YK_Sprite *debug_draw)
{
  for (int i = 0; i < 2; i++)
  {
    if (has_component(i, POSITION_COMPONENT) && has_component(i, COLLIDER_COMPONENT))
    {
      YK_Vec3f *_pos = yk_yektor_get(&pos_comps, i);
      YK_Aabb *_aabb = yk_yektor_get(&aabb_comps, i);

      _aabb->pos.x = _pos->x;
      _aabb->pos.y = _pos->y;

      YK_Sprite _a = *debug_draw;
      _a.transform.pos = *_pos;

      yk_renderer2d_render_sprite(ren, &_a);
    }
  }
}

void yk_ecs_collide_system(f4 delta)
{
  for (int i = 0; i < 1; i++)
  {
    if (has_component(i, POSITION_COMPONENT) && has_component(i, COLLIDER_COMPONENT))
    {
      YK_Vec3f *_pos = yk_yektor_get(&pos_comps, i);
      YK_Aabb *_aabb = yk_yektor_get(&aabb_comps, i);
      YK_Aabb *_aabb2 = yk_yektor_get(&aabb_comps, i + 1);

      if (yk_physics_colliding(_aabb, _aabb2))
      {
        YK_Vec3f a = yk_physics_get_overlap_distance(_aabb,_aabb2);
        *_pos = yk_math_vec3f_sub(_pos, &a);
      }
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
  cam2d.zoom = 1.f;

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, &win);

  yk_yektor_innit(&pos_comps, 10, sizeof(YK_Vec3f));
  yk_yektor_innit(&sprite_comps, 10, sizeof(YK_Sprite));
  yk_yektor_innit(&aabb_comps, 10, sizeof(YK_Aabb));

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  yk_renderer2d_set_bg(0.2f, 0.3f, 0.3f, 1.f);
  int gooba = yk_ecs_create_entity();
  {

    YK_Sprite _sprite;
    yk_sprite_innit(&_sprite, "yk-res/textures/default.jpg");
    yk_yektor_push(&sprite_comps, &_sprite);

    YK_Vec3f _pos = {-1.f, 0.f, -1.f};
    yk_yektor_push(&pos_comps, &_pos);

    YK_Aabb _aabb;
    _aabb.pos.x = _pos.x;
    _aabb.pos.y = _pos.y;
    _aabb.size.x = 1.f;
    _aabb.size.y = 1.f;
    yk_yektor_push(&aabb_comps, &_aabb);

    comp_mask[gooba] = POSITION_COMPONENT | SPRITE_COMPONENT | COLLIDER_COMPONENT;
  }

  int player = yk_ecs_create_entity();
  {

    YK_Sprite _sprite;
    yk_sprite_innit(&_sprite, "yk-res/textures/yk.png");
    yk_yektor_push(&sprite_comps, &_sprite);

    YK_Vec3f _pos = {0.f, 0.f, -1.f};
    yk_yektor_push(&pos_comps, &_pos);

    py.cam = &cam2d;

    YK_Aabb _aabb;
    _aabb.pos.x = _pos.x;
    _aabb.pos.y = _pos.y;
    _aabb.size.x = 1.f;
    _aabb.size.y = 1.f;
    yk_yektor_push(&aabb_comps, &_aabb);

    comp_mask[player] = POSITION_COMPONENT | SPRITE_COMPONENT | PLAYER_COMPONENT | COLLIDER_COMPONENT;
  }

  int gooba2 = yk_ecs_create_entity();
  {
    {
      YK_Sprite _sprite;
      yk_sprite_innit(&_sprite, "yk-res/textures/cullen.png");
      yk_yektor_push(&sprite_comps, &_sprite);
    }

    {
      YK_Vec3f _pos = {1.f, 0.f, -1.f};
      yk_yektor_push(&pos_comps, &_pos);
    }

    comp_mask[gooba2] = POSITION_COMPONENT | SPRITE_COMPONENT;
  }

  YK_Sprite _debug_draw;
  yk_sprite_innit(&_debug_draw, "yk-res/textures/outline.png");

  // get cullen to help tomorrow. add him as a sprite to help see pattern?

  while (yk_window_is_running(&win))
  {

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    // debug_input(&cam2d, delta_time);

    yk_renderer2d_run(&ren2d, &win);

    yk_ecs_player_system(player, delta_time);

    yk_ecs_physics_system(&ren2d, &_debug_draw);
    yk_ecs_collide_system(delta_time);

    yk_ecs_sprite_render_system(&ren2d);

    yk_window_run(&win);
  }

  yk_sprite_destroy(&_debug_draw);
  yk_yektor_destroy(&pos_comps);
  yk_yektor_destroy(&sprite_comps);
  yk_window_destroy(&win);

  return 0;
}