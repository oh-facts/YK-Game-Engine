#include <Renderer.h>
#include <FileReader.h>
#include <stb/stb_image.h>

Sprite create_sprite(const char *imageFile)
{
    Sprite out;
    out.shaderProgram = create_shader("res\\shaders\\default.vert", "res\\shaders\\default.frag");
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.875f, 0.0f, 1.0f, 1.0f,      // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.564f, 0.784f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 0.875f, 0.0f, 0.0f, 0.0f,    // bottom left
        -0.5f, 0.5f, 0.0f, 0.129f, 0.329f, 0.647f, 0.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};

    glGenVertexArrays(1, &out.vao);
    glGenBuffers(1, &out.vbo);
    glGenBuffers(1, &out.ebo);

    glBindVertexArray(out.vao);

    glBindBuffer(GL_ARRAY_BUFFER, out.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out.ebo);
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
    stbi_set_flip_vertically_on_load(1);
    unsigned char *bytes = stbi_load(imageFile, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &out.texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, out.texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(out.shaderProgram, "tex0");
    glUseProgram(out.shaderProgram);
    glUniform1i(tex0Uni, 0);

    return out;
}

void render_sprite(Sprite *sprite)
{
    glUseProgram(sprite->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, sprite->texture);

    glBindVertexArray(sprite->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/* This function is just here. Don't mind him.*/

void renderer_update()
{
}

void cleanup_sprite(Sprite *sprite)
{
    glDeleteVertexArrays(1, &(sprite->vao));
    glDeleteBuffers(1, &(sprite->vbo));
    glDeleteBuffers(1, &(sprite->ebo));

    glDeleteTextures(1, &(sprite->texture));

    glDeleteProgram(sprite->shaderProgram);
}

GLuint create_shader(const char *vertexFile, const char *fragmentFile)
{

    const char *vertexShaderSource = getFileContents(vertexFile);
    const char *fragmentShaderSource = getFileContents(fragmentFile);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program, vertexShader);
    glAttachShader(shader_program, fragmentShader);
    glLinkProgram(shader_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader_program;
}
