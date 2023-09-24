#include <yk/yk_renderer2d.h>

YK_Yektor yk_rects;

YK_Texture white_square;

i4 draw_calls;

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
void yk_rect_innit(YK_Rect *out)
{
    out->shader_program = yk_shader_create("yk-res/shaders/default/rect.vert", "yk-res/shaders/default/rect.frag");

   f4 vertices[] = {
    // Position           // Texture Coords
    0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
   -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    };

    u4 indices[] = {
    0, 1, 3,
    1, 2, 3
    };

    GLuint vbo, ebo;
    glGenVertexArrays(1, &out->vertex_arrays);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(out->vertex_arrays);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // texture attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    GLuint tex0Uni = glGetUniformLocation(out->shader_program, "tex0");
    glUseProgram(out->shader_program);
    glUniform1i(tex0Uni, 0);
}

void yk_renderer2d_render_rect(YK_Renderer2d *renderer, YK_Rect *rect, YK_Transform *transform, YK_Vec4f *col)
{
    glUseProgram(rect->shader_program);
    glBindVertexArray(rect->vertex_arrays);
    glBindTexture(GL_TEXTURE_2D, white_square.id);

    u4 modelLoc = glGetUniformLocation(rect->shader_program, "model");
    u4 viewLoc = glGetUniformLocation(rect->shader_program, "view");
    u4 projectionLoc = glGetUniformLocation(rect->shader_program, "projection");
    u4 colorLoc = glGetUniformLocation(rect->shader_program, "color");

    {
        YK_Mat4f out;
        out = yk_mat4f_identity();

        yk_math_transform_translate(&out, &transform->pos);

        YK_Vec3f _rot = transform->rot;
        yk_math_transform_rotate(&out, _rot.x, &YK_WORLD_RIGHT);
        yk_math_transform_rotate(&out, _rot.y, &YK_WORLD_UP);
        yk_math_transform_rotate(&out, _rot.z, &YK_WORLD_FORWARD);

        yk_math_transform_scale(&out, &transform->scale);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &out.m00);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));
    glUniform4f(colorLoc, col->r, col->g, col->b, col->a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    draw_calls++;

    glBindVertexArray(0);
}

void yk_renderer2d_render_rect_sprite(YK_Renderer2d *renderer, YK_Rect *rect, YK_Texture *texture)
{

}

void yk_rect_destroy(YK_Rect *out)
{
    glDeleteVertexArrays(1, &(out->vertex_arrays));
    glDeleteProgram(out->shader_program);
}

void yk_sprite_innit(YK_Sprite *out, const char *texture_path)
{

    yk_vec3f_mem_set(&out->transform.pos, 0);
    yk_vec3f_mem_set(&out->transform.scale, 1);
    yk_vec3f_mem_set(&out->transform.rot, 0);

    out->shaderProgram = yk_shader_create("yk-res/shaders/rect/default.vert", "yk-res/shaders/rect/default.frag");

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
    glGenVertexArrays(1, &out->vertex_arrays);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(out->vertex_arrays);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

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

    out->texture = yk_texture_create(texture_path);

    GLuint tex0Uni = glGetUniformLocation(out->shaderProgram, "tex0");
    glUseProgram(out->shaderProgram);
    glUniform1i(tex0Uni, 0);
}

void yk_sprite_destroy(YK_Sprite *sprite)
{
    glDeleteVertexArrays(1, &(sprite->vertex_arrays));
    glDeleteProgram(sprite->shaderProgram);
}

YK_Mat4f yk_sprite_get_model_mat(YK_Sprite *sprite)
{
    YK_Mat4f out;
    out = yk_mat4f_identity();

    YK_Transform _trans = sprite->transform;
    yk_math_transform_translate(&out, &_trans.pos);

    YK_Vec3f _rot = _trans.rot;
    yk_math_transform_rotate(&out, _rot.x, &YK_WORLD_RIGHT);
    yk_math_transform_rotate(&out, _rot.y, &YK_WORLD_UP);
    yk_math_transform_rotate(&out, _rot.z, &YK_WORLD_FORWARD);

    yk_math_transform_scale(&out, &_trans.scale);

    return out;
}

void yk_sprite_set_texture(const char *texture_path)
{
}

void yk_renderer2d_innit(YK_Renderer2d *ren, YK_Camera2d *current_cam, YK_Window *win)
{
    ren->current_cam = current_cam;
    ren->proj_mat = yk_camera2d_get_projection_matrix(current_cam, (f4)win->width / win->height);
    ren->view_mat = yk_camera2d_get_view_matrix(current_cam);

    white_square = yk_texture_create("yk-res/textures/white_square.png");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    draw_calls = 0;
}

void yk_renderer2d_run(YK_Renderer2d *renderer, YK_Window *win)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->view_mat = yk_camera2d_get_view_matrix(renderer->current_cam);

    f4 _aspect_ratio = (f4)win->width / win->height;

    // make some kind of callback so you only need to recalculate when updating zoom/aspect ratio
    renderer->proj_mat = yk_camera2d_get_projection_matrix(renderer->current_cam, _aspect_ratio);

    draw_calls = 0;
}

void yk_renderer2d_render_sprite(YK_Renderer2d *renderer, YK_Sprite *sprite)
{
    glUseProgram(sprite->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, sprite->texture.id);
    glBindVertexArray(sprite->vertex_arrays);

    u4 modelLoc = glGetUniformLocation(sprite->shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(sprite->shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(sprite->shaderProgram, "projection");

    {
        YK_Mat4f model = yk_sprite_get_model_mat(sprite);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model.m00);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void yk_renderer2d_set_bg(f4 r, f4 g, f4 b, f4 a)
{
    glClearColor(r, g, b, a);
}