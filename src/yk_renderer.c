#include <yk/yk_renderer.h>
#include <yk/yk_file_reader.h>
#include <stb/stb_image.h>

YK_Sprite yk_sprite_create(const char *imageFile)
{
    YK_Sprite out;
    out.shaderProgram = yk_shader_create("yk-res/shaders/default.vert", "yk-res/shaders/default.frag");
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

YK_Sprite yk_cube_create(const char *imageFile)
{
    YK_Sprite out;
    out.pos.x = 0.f;
    out.pos.y = 0.f;
    out.pos.z = 0.f;
    out.model_mat = yk_mat4f_identity();

    out.shaderProgram = yk_shader_create("yk-res/shaders/cube/default.vert", "yk-res/shaders/cube/default.frag");
    float vertices[] = {
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    
     0.5f, -0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    
    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
};


float indices[] = {
     0.f,  1.f,  2.f,   0.f,  2.f,  3.f,
     4.f,  5.f,  6.f,   4.f,  6.f,  7.f,
     8.f,  9.f, 10.f,   8.f, 10.f, 11.f,
    12.f, 13.f, 14.f,  12.f, 14.f, 15.f,
    16.f, 17.f, 18.f,  16.f, 18.f, 19.f,
    20.f, 21.f, 22.f,  20.f, 22.f, 23.f
};


    glGenVertexArrays(1, &out.vao);
    glGenBuffers(1, &out.vbo);
    glGenBuffers(1,&out.ebo);

    glBindVertexArray(out.vao);

    glBindBuffer(GL_ARRAY_BUFFER, out.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /*
        // col attrib
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    */
    // texture attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

void yk_cube_set_pos(YK_Sprite *sprite, YK_Vec3f *pos)
{
    sprite->model_mat = yk_mat4f_identity();
    yk_maths_transform_translate(&sprite->model_mat, pos);
}

void yk_cube_move(YK_Sprite *sprite, YK_Vec3f *pos)
{
    yk_maths_transform_translate(&sprite->model_mat, pos);
}

void yk_render_cube(YK_Renderer *renderer, YK_Sprite *sprite)
{
    u4 modelLoc = glGetUniformLocation(sprite->shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(sprite->shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(sprite->shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(sprite->model_mat.m00));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));

    glUseProgram(sprite->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, sprite->texture);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void yk_cube_cleanup(YK_Sprite *sprite)
{
}

void yk_render_sprite(YK_Renderer *renderer, YK_Sprite *sprite)
{
    u4 modelLoc = glGetUniformLocation(sprite->shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(sprite->shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(sprite->shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(sprite->model_mat.m00));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));

    glUseProgram(sprite->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, sprite->texture);

    glBindVertexArray(sprite->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/* This function is just here. Don't mind him.*/

void yk_renderer_innit(YK_Renderer *renderer, YK_Camera *current_cam)
{
    renderer->current_cam = current_cam;
}

void yk_renderer_run(YK_Renderer *renderer, YK_Window *win)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    YK_Camera *cam = renderer->current_cam;

    renderer->view_mat = yk_mat4f_identity();
    {
        YK_Vec3f _temp = yk_math_vec3f_add(&cam->pos, &cam->front);
        renderer->view_mat = yk_look_at(&cam->pos, &_temp, &cam->up);
    }

    renderer->proj_mat = yk_mat4f_identity();
    renderer->proj_mat = yk_mat4f_perspective(cam->fov * DEG_TO_RAD, ((f4)win->width / win->height), 0.1f, 100.f);
}

void yk_sprite_cleanup(YK_Sprite *sprite)
{
    glDeleteVertexArrays(1, &(sprite->vao));
    glDeleteBuffers(1, &(sprite->vbo));
    glDeleteBuffers(1, &(sprite->ebo));

    glDeleteTextures(1, &(sprite->texture));

    glDeleteProgram(sprite->shaderProgram);
}

GLuint yk_shader_create(const char *vertexFile, const char *fragmentFile)
{

    const char *vertexShaderSource = yk_file_reader(vertexFile);
    const char *fragmentShaderSource = yk_file_reader(fragmentFile);

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
