#include <App.hpp>

#include <FileReader.hpp>

namespace AE
{
  namespace App
  {


  }
  void App::run()
  {

    // Vertex Shader source code
    std::string vertexShaderSourceStr = util::getFileContents("res\\default.vert");
    const char *vertexShaderSource = vertexShaderSourceStr.c_str();

    std::string fragmentShaderSourceStr = util::getFileContents("res\\default.frag");
    const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

      float vertices[] = {
          0.5f, 0.5f, 0.0f,          1.0f,0.875f,0.0f,             // top right
          0.5f, -0.5f, 0.0f,         1.0f,0.564f,0.784f,               // bottom right
          -0.5f, -0.5f, 0.0f,        1.0f,0.875f,0.0f,               // bottom left
          -0.5f, 0.5f, 0.0f,          0.129f,0.329f, 0.647f,                // top left
      };

      unsigned int indices[] = {
          0, 1, 3,
          1, 2, 3};

      unsigned int vbo;
      unsigned int vao;
      unsigned int ebo;

      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glGenBuffers(1, &ebo);

      glBindVertexArray(vao);

      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      //pos attrib
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
      glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

      glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

      while (!glfwWindowShouldClose(win))
      {

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

      
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(win);
        glfwPollEvents();
      }

      glDeleteVertexArrays(1, &vao);
      glDeleteBuffers(1, &vbo);
      glDeleteBuffers(1, &ebo);

      glDeleteProgram(shaderProgram);
      glfwDestroyWindow(win);
    }
    void quit()
    {
      glfwTerminate();
    }

  }
}