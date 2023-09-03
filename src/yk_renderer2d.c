#include <yk/yk_renderer2d.h>

/*
YK_Rect yk_renderer2d_create_rect()
{
    YK_Rect out;
    out.model_mat = yk_mat4f_identity();
    out.pos.x = 0;
    out.pos.y = 0;
    out.pos.z = 0;

    out.shaderProgram = yk_shader_create("yk-res/shaders/rect/default.vert", "yk-res/shaders/rect/default.frag");

    f4 vertices[] =
        {
            // Position           // Texture Coords      // Color
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.875f, 0.0f, 0.0f,      // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.564f, 0.784f, 1.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.875f, 0.0f, 0.0f,    // bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.129f, 0.329f, 0.647f, // top left
        };

    u4 indices[] =
        {
            0, 1, 3,
            1, 2, 3};

    GLuint vbo, ebo;
    glGenVertexArrays(1, &out.vertex_arrays);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(&out.vertex_arrays);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // texture attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // col attrib
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void yk_renderer2d_destroy_rect(YK_Rect *rect)
{
    glDeleteVertexArrays(1, &(rect->vertex_arrays));
    glDeleteProgram(rect->shaderProgram);
}

*/

YK_Sprite yk_sprite_create(const char *texture_path)
{
    YK_Sprite out;
    out.model_mat = yk_mat4f_identity();
    out.pos.x = 0;
    out.pos.y = 0;
    out.pos.z = 0;

    out.shaderProgram = yk_shader_create("yk-res/shaders/rect/default.vert", "yk-res/shaders/rect/default.frag");

    f4 vertices[] =
        {
            // Position           // Texture Coords      // Color
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.875f, 0.0f, 0.0f,      // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.564f, 0.784f, 1.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.875f, 0.0f, 0.0f,    // bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.129f, 0.329f, 0.647f, // top left
        };

    u4 indices[] =
        {
            0, 1, 3,
            1, 2, 3};

    GLuint vbo, ebo;
    glGenVertexArrays(1, &out.vertex_arrays);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(out.vertex_arrays);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // texture attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // col attrib
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    out.texture = yk_texture_create(texture_path);

    GLuint tex0Uni = glGetUniformLocation(out.shaderProgram, "tex0");
    glUseProgram(out.shaderProgram);
    glUniform1i(tex0Uni, 0);

    return out;
}

void yk_sprite_destroy(YK_Sprite *sprite)
{
    glDeleteVertexArrays(1, &(sprite->vertex_arrays));
    glDeleteProgram(sprite->shaderProgram);
}

void yk_sprite_set_pos(YK_Sprite *sprite, YK_Vec3f *pos)
{
    sprite->pos = *pos;
    sprite->model_mat = yk_mat4f_identity();
    yk_maths_transform_translate(&sprite->model_mat, pos);
}

void yk_sprite_set_texture(const char *texture_path)
{
}

void yk_renderer2d_innit(YK_Renderer2d *ren, YK_Camera2d *current_cam, YK_Window *win)
{
    ren->current_cam = current_cam;
    ren->proj_mat = yk_camera2d_get_projection_matrix(current_cam, (f4)win->width / win->height);
    ren->view_mat = yk_camera2d_get_view_matrix(current_cam);
}

void yk_renderer2d_run(YK_Renderer2d *renderer, YK_Window *win)
{
    glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->view_mat = yk_camera2d_get_view_matrix(renderer->current_cam);

    f4 _aspect_ratio = (f4)win->width / win->height;

    //make some kind of callback so you only need to recalculate when updating zoom/aspect ratio
    renderer->proj_mat = yk_camera2d_get_projection_matrix(renderer->current_cam, _aspect_ratio);
}

void yk_renderer2d_render_sprite(YK_Renderer2d *renderer, YK_Sprite *sprite)
{
    u4 modelLoc = glGetUniformLocation(sprite->shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(sprite->shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(sprite->shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(sprite->model_mat.m00));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));

    glUseProgram(sprite->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, sprite->texture.id);

    glBindVertexArray(sprite->vertex_arrays);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}