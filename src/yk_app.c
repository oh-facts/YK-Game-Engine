#include <yk/yk_app.h>
#include <yk/yk_renderer.h>
#include <time.h>



YK_Vec3f cameraPos = {0.0f, 0.0f, 3.0f};
YK_Vec3f cameraFront = {0.0f, 0.0f, -1.0f};
YK_Vec3f cameraUp = {0.0f, 1.0f, 0.0f};

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    YK_Vec3f temp = yk_math_vec3f_mul_s(&cameraFront, cameraSpeed);
    cameraPos = yk_math_vec3f_add(&cameraPos, &temp);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    YK_Vec3f temp = yk_math_vec3f_mul_s(&cameraFront, cameraSpeed);
    cameraPos = yk_math_vec3f_sub(&cameraPos, &temp);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    YK_Vec3f temp = yk_math_vec3f_cross(&cameraFront, &cameraUp);
    YK_Vec3f temp2 = yk_vec3f_normalize(&temp);
    YK_Vec3f temp3 = yk_math_vec3f_mul_s(&temp2, cameraSpeed);
    cameraPos = yk_math_vec3f_sub(&cameraPos, &temp3);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    YK_Vec3f temp = yk_math_vec3f_cross(&cameraFront, &cameraUp);
    YK_Vec3f temp2 = yk_vec3f_normalize(&temp);
    YK_Vec3f temp3 = yk_math_vec3f_mul_s(&temp2, cameraSpeed);
    cameraPos = yk_math_vec3f_add(&cameraPos, &temp3);
  }
}

YK_API void yk_app_innit(YK_App *app)
{
  yk_window_innit(&app->m_win);
}

YK_API void yk_app_run(YK_App *app)
{

  // YK_Sprite myFace = yk_sprite_create("res/textures/default.jpg");
  YK_Sprite myFace = yk_cube_create("res/textures/default.jpg");

  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {
    glfwSwapInterval(0);
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processInput(app->m_win.win_ptr);

    YK_Mat4f model = yk_mat4f_identity();
    YK_Mat4f view = yk_mat4f_identity();
    YK_Mat4f projection;

    yk_maths_transform_translate(&model, &(YK_Vec3f){0.f, 0.f, -2.f});
    yk_math_transform_rotate(&model, glfwGetTime(), &(YK_Vec3f){1.f, 1.f, 0.f});
    // yk_maths_transform_scale(&model, &(YK_Vec3f){0.5f, 0.5f, 0.5f});

    // yk_maths_transform_translate(&view, &(YK_Vec3f){0.0f, 0.f, -5.f});

    /*
        {
          YK_Vec3f temp = yk_math_vec3f_sub(&camPos, &camTarget);
          camDir = yk_vec3f_normalize(&temp);
        }
        */

    {
      YK_Vec3f _temp = yk_math_vec3f_add(&cameraPos, &cameraFront);
      view = yk_look_at(&cameraPos, &_temp, &cameraUp);
    }

    projection = yk_mat4f_perspective(45.f * DEG_TO_RAD, ((f4)app->m_win.width/app->m_win.height), 0.1f, 100.f);
    
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
YK_API void yk_app_quit(YK_App *app)
{
  glfwTerminate();
  glfwDestroyWindow(app->m_win.win_ptr);
}
