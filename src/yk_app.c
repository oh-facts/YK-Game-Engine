#include <yk_app.h>

#include <yk_renderer.h>
#include <time.h>

void yk_app_innit(YK_App *app)
{
  app->m_win = yk_window_create();
}

void yk_app_run(YK_App *app)
{

  // YK_Sprite myFace = yk_sprite_create("res/textures/default.jpg");
  YK_Sprite myFace = yk_cube_create("res/textures/default.jpg");

  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    YK_Mat4f model = yk_mat4f_identity();
    YK_Mat4f view = yk_mat4f_identity();
    YK_Mat4f projection;

    model = yk_math_transform_rotate(&model, glfwGetTime(), &(YK_Vec3f){0.f, 1.f, 0.f});
    yk_maths_transform_translate(&view, &(YK_Vec3f){0.0f, 0.f, -5.f});
    projection = yk_mat4f_perspective(45.f * DEG_TO_RAD, WIDTH / HEIGHT, 0.1f, 100.f);

    u4 modelLoc = glGetUniformLocation(myFace.shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(myFace.shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(myFace.shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(model.m00));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(view.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(projection.m00));

    /*
      yk_maths_transform_translate(&model, &(YK_Vec3f){-0.5f, -0.5f, 0.0f});
      yk_maths_transform_rotate(&model, (float)glfwGetTime(), &(YK_Vec3f){0.0f, 0.0f, 1.f});
      yk_math_transform_scale(&model, &(YK_Vec3f){0.5f, 0.5f, 0.0f});
    */

    // yk_render_sprite(&myFace);
    yk_render_cube(&myFace);

    glfwSwapBuffers(app->m_win.win_ptr);
    glfwPollEvents();
  }
  // yk_sprite_cleanup(&myFace);
}
void yk_app_quit(YK_App *app)
{
  glfwTerminate();
  glfwDestroyWindow(app->m_win.win_ptr);
}
