#include <yk/yk_app.h>
#include <yk/yk_renderer.h>
#include <time.h>
#include <yk/yk_camera.h>

b1 full_screen_toggle = true;

void processInput(YK_Window *win)
{

  if (yk_input_is_key_tapped(YK_KEY_ESCAPE))
  {
    glfwSetWindowShouldClose(win->win_ptr, true);
  }

  if (yk_input_is_key_held(YK_KEY_LEFT_ALT) && yk_input_is_key_tapped(YK_KEY_ENTER))
  {
    if (full_screen_toggle)
    {
      full_screen_toggle = false;
      yk_window_resize(win, 1920, 1080);
    }
    else
    {
      full_screen_toggle = true;
      yk_window_resize(win, WIDTH, HEIGHT);
    }
  }
}

YK_API void yk_app_innit(YK_App *app)
{
  yk_window_innit(&app->m_win);
}

YK_API void yk_app_run(YK_App *app)
{

  f4 delta_time = 0.0f;
  f4 last_frame = 0.0f;

  YK_Camera cam;
  yk_camera_innit(&cam);

  YK_Renderer ren;
  yk_renderer_innit(&ren, &cam);

  YK_Sprite myFaces[10];

  srand(time(NULL));

  for (int i = 0; i < 10; i++)
  {
    myFaces[i] = yk_cube_create("yk-res/textures/default.jpg");

    float rx = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
    float ry = ((float)rand() / RAND_MAX) * 5.f - 2.5f;
    float rz = ((float)rand() / RAND_MAX) * -10.0f;
    yk_cube_set_pos(&myFaces[i], &(YK_Vec3f){rx, ry, rz});
  }

  // yk_maths_transform_translate(&myFace.model_mat, &(YK_Vec3f){0.f, 0.f, -3.f});
  // yk_math_transform_rotate(&myFace.model_mat, glfwGetTime(), &(YK_Vec3f){1.f, 1.f, 0.f});
  // yk_maths_transform_scale(&myFace.model_mat, &(YK_Vec3f){0.5f, 0.5f, 0.5f});

  // projection = yk_mat4f_ortho(-0.5f, 0.5f, -0.5f, 0.5f, 2.f, 100.f);
  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {

    processInput(&app->m_win);

    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    yk_camera_update(&cam, delta_time);

    yk_renderer_run(&ren, &app->m_win);

    for (int i = 0; i < 10; i++)
    {
      yk_render_cube(&ren, &myFaces[i]);
    }

    yk_window_run(&app->m_win);
  }
}
YK_API void yk_app_quit(YK_App *app)
{
  yk_window_quit(&app->m_win);
}

// projection = yk_mat4f_ortho(-0.5f, 0.5f, -0.5f, 0.5f, 2.f, 100.f);