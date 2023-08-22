#include <yk_app.h>

#include <yk_renderer.h>
#include <time.h>

void yk_app_innit(YK_App *app)
{
  app->m_win = yk_window_create();
}

void yk_app_run(YK_App *app)
{

  YK_Sprite myFace = yk_sprite_create("res/textures/default.jpg");

  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    YK_Mat4f trans = yk_mat4f_identity();

    trans = yk_math_transform_translate(&trans, &(YK_Vec3f){0.5f, 0.5f, 0.0f});
    trans = yk_math_transform_rotate(&trans, (float)glfwGetTime(), &(YK_Vec3f){0.0f, 0.0f, 1.0f});
    trans = yk_math_transform_scale(&trans, &(YK_Vec3f){0.5f, 0.5f, 0.0f});

    u4 transformLoc = glGetUniformLocation(myFace.shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &(trans.m00));

    yk_render_sprite(&myFace);
    glfwSwapBuffers(app->m_win.win_ptr);
    glfwPollEvents();
  }
  yk_sprite_cleanup(&myFace);
}
void yk_app_quit(YK_App *app)
{
  glfwTerminate();
  glfwDestroyWindow(app->m_win.win_ptr);
}
