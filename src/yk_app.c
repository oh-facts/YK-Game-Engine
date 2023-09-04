#include <yk/yk_app.h>

/*

YK_API void yk_app_is_running(YK_App *app)
{
  //return !glfwWindowShouldClose(app->m_win.win_ptr);
}

YK_API void yk_app_innit(YK_App *app)
{
  yk_window_innit(&app->m_win);
  yk_scene_innit(&app->m_scene);
 // yk_renderer2d_innit(&app->m_ren);
  app->delta_time = 0.0f;
  app->last_frame = 0.0f;
}

YK_API void yk_app_run(YK_App *app)
{

  // int ent1 = yk_ecs_create_entity();


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



  //yk_window_run(&app->m_win);
//}

/*
  for (int i = 0; i < 10; i++)
  {
    yk_sprite_destroy(&babbits[i]);
  }

  */

/*
YK_API void yk_app_quit(YK_App *app)
{
  yk_window_quit(&app->m_win);
}

*/