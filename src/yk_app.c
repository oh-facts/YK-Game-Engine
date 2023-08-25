#include <yk/yk_app.h>
#include <yk/yk_renderer.h>
#include <time.h>
#include <yk/yk_camera.h>

void processInput(GLFWwindow *window)
{
  /*
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);


  */
}

YK_API void yk_app_innit(YK_App *app)
{
  yk_window_innit(&app->m_win);
  glfwSetInputMode(app->m_win.win_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

YK_API void yk_app_run(YK_App *app)
{
  YK_Sprite myFace = yk_cube_create("yk-res/textures/default.jpg");
  f4 delta_time = 0.0f;
  f4 last_frame = 0.0f;

  YK_Camera camera;
  yk_camera_innit(&camera);

  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {
    glfwSwapInterval(0);
    f4 current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processInput(app->m_win.win_ptr);

    YK_Mat4f model = yk_mat4f_identity();
    YK_Mat4f view = yk_mat4f_identity();
    YK_Mat4f projection;

    yk_maths_transform_translate(&model, &(YK_Vec3f){0.f, 0.f, -2.f});
    yk_math_transform_rotate(&model, glfwGetTime(), &(YK_Vec3f){1.f, 1.f, 0.f});
    yk_maths_transform_scale(&model, &(YK_Vec3f){0.5f, 0.5f, 0.5f});

    yk_camera_update(&camera, delta_time);
    yk_input_mouse_scroll = 0;

    // yk_maths_transform_translate(&view, &(YK_Vec3f){0.0f, 0.f, -5.f});

    {
        YK_Vec3f _temp = yk_math_vec3f_add(&camera.pos, &camera.front);
        view = yk_look_at(&camera.pos, &_temp, &camera.up);
    }

    projection = yk_mat4f_perspective(camera.fov* DEG_TO_RAD, ((f4)app->m_win.width/app->m_win.height), 0.1f, 100.f);

    u4 modelLoc = glGetUniformLocation(myFace.shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(myFace.shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(myFace.shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(model.m00));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(view.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(projection.m00));

    yk_render_cube(&myFace);

    glfwSwapBuffers(app->m_win.win_ptr);
    glfwPollEvents();
  }
}
YK_API void yk_app_quit(YK_App *app)
{
  glfwTerminate();
  glfwDestroyWindow(app->m_win.win_ptr);
}
