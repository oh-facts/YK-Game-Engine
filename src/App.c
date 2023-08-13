#include <App.h>

#include <Renderer.h>

void innit(App *app)
{
  app->m_win = create_window();
}

void run(App *app)
{

  Sprite myFace = create_sprite("res/textures/default.jpg");

  while (!glfwWindowShouldClose(app->m_win.win_ptr))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    render_sprite(&myFace);

    glfwSwapBuffers(app->m_win.win_ptr);
    glfwPollEvents();
  }

  cleanup_sprite(&myFace);
}
void quit(App *app)
{
  glfwTerminate();
  glfwDestroyWindow(app->m_win.win_ptr);
}
