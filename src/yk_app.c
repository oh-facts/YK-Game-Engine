#include <yk/yk_app.h>

#include <yk/yk_renderer2d.h>
#include <yk/yk_camera2d.h>

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

YK_API void yk_app_innit(YK_App *app)
{
  yk_window_innit(&app->m_win);
  yk_scene_innit(&app->m_scene);
}

YK_API void yk_app_run(YK_App *app)
{

  f4 delta_time = 0.0f;
  f4 last_frame = 0.0f;
  /**/
  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, &app->m_win);

  // int ent1 = yk_ecs_create_entity();

  /*
   YK_Sprite babbits[20];

    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
      babbits[i] = yk_sprite_create("yk-res/textures/default.jpg");

      float rx = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
      float ry = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
      float rz = ((float)rand() / RAND_MAX) * -10.0f;
      yk_sprite_set_pos(&babbits[i], &(YK_Vec3f){rx, ry, -1.f});
    }
  */
  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    yk_camera2d_update(&cam2d, delta_time);
    debug_input(&cam2d, delta_time);

    yk_renderer2d_run(&ren2d, &app->m_win);

    for (int i = 0; i < app->m_scene.num_entities; i++)
    {

     // yk_renderer2d_render_sprite(&ren2d, );
      // printf("%f \n",babbits[i].pos.x);
    }

    yk_window_run(&app->m_win);
  }

  /*
    for (int i = 0; i < 10; i++)
    {
      yk_sprite_destroy(&babbits[i]);
    }

    */
}

YK_API void yk_app_quit(YK_App *app)
{
  yk_window_quit(&app->m_win);
}