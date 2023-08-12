#include <App.hpp>
#include <stb/stb_image.hpp>
#include <Renderer.hpp>

namespace AE
{

  void App::innit()
  {
  }
  void App::run()
  {

    unsigned int shaderProgram = create_shader("res\\shaders\\default.vert", "res\\shaders\\default.frag");

    float vertices[] = {
        0.5f, 0.5f, 0.0f,           1.0f, 0.875f, 0.0f,         1.0f, 1.0f,    // top right
        0.5f, -0.5f, 0.0f,          1.0f, 0.564f, 0.784f,       1.0f, 0.0f,    // bottom right
        -0.5f, -0.5f, 0.0f,         1.0f, 0.875f, 0.0f,         0.0f, 0.0f,    // bottom left
        -0.5f, 0.5f, 0.0f,          0.129f, 0.329f, 0.647f,     0.0f, 1.0f,    // top left
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

    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // col attrib
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture attrib
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // texture
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load("res\\textures\\default.jpg", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D,0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram,"tex0");
    glUseProgram(shaderProgram);
    glUniform1i(tex0Uni,0);


    while (!glfwWindowShouldClose(m_win.win_ptr))
    {

      // render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindTexture(GL_TEXTURE_2D, texture);

      glBindVertexArray(vao);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      glfwSwapBuffers(m_win.win_ptr);
      glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteTextures(1, &texture);

    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(m_win.win_ptr);
  }
  void App::quit()
  {
    glfwTerminate();
  }

}
