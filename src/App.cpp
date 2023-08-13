#include <App.hpp>

#include <Renderer.hpp>
#include <glm/glm.hpp>

namespace AE
{

  void App::innit()
  {
  }
  void App::run()
  {

    Sprite myFace = create_sprite("res/textures/default.jpg");

    while (!glfwWindowShouldClose(m_win.win_ptr))
    {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      render_sprite(myFace);

      glfwSwapBuffers(m_win.win_ptr);
      glfwPollEvents();
    }

    glfwDestroyWindow(m_win.win_ptr);

    cleanup_sprite(myFace);
    
  }
  void App::quit()
  {
    glfwTerminate();
  }

}
