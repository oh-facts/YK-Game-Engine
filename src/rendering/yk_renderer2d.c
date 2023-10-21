#include <yk/rendering/yk_renderer2d.h>
#include <glad/glad.h>

struct YK_Rect
{
    GLuint shader_program;
    GLuint vertex_arrays;
};

typedef struct YK_Rect YK_Rect;

struct YK_Line
{
    GLuint shader_program;
    GLuint vertex_arrays;
};

typedef struct YK_Line YK_Line;

void yk_rect_innit(YK_Rect *out);
void yk_rect_destroy(YK_Rect *out);

void yk_line_innit(YK_Line *out);
void yk_line_destroy(YK_Line *out);

YK_Texture white_square;

YK_Rect yk_rect_default;

YK_Line yk_line_default;

i4 draw_calls;

void yk_rect_innit(YK_Rect *out)
{
    out->shader_program = yk_shader_create("yk-res/shaders/default/rect.vert", "yk-res/shaders/default/rect.frag");

    f4 vertices[] = {
        // Position           // Texture Coords
        0.5f,
        0.5f,
        0.0f,
        1.0f,
        1.0f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.0f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        1.0f,
    };

    u4 indices[] = {
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

void yk_rect_destroy(YK_Rect *out)
{
    glDeleteVertexArrays(1, &(out->vertex_arrays));
    glDeleteProgram(out->shader_program);
}

void yk_renderer2d_innit(YK_Renderer2d *ren, YK_Camera2d *current_cam, YK_Window *win)
{
    ren->current_cam = current_cam;
    ren->proj_mat = yk_camera2d_get_projection_matrix(current_cam, yk_window_aspect_ratio(win));
    ren->view_mat = yk_camera2d_get_view_matrix(current_cam);

    white_square = yk_texture_create("yk-res/textures/white_square.png");

    yk_rect_innit(&yk_rect_default);
    yk_line_innit(&yk_line_default);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    draw_calls = 0;
}

void yk_renderer2d_begin_draw(YK_Renderer2d *renderer, YK_Window *win)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->view_mat = yk_camera2d_get_view_matrix(renderer->current_cam);

    // make some kind of callback so you only need to recalculate when updating zoom/aspect ratio
    renderer->proj_mat = yk_camera2d_get_projection_matrix(renderer->current_cam, yk_window_aspect_ratio(win));

    draw_calls = 0;
}

void yk_renderer2d_set_bg(f4 r, f4 g, f4 b, f4 a)
{
    glClearColor(r, g, b, a);
}

void yk_renderer2d_destroy()
{
    yk_rect_destroy(&yk_rect_default);
    yk_line_destroy(&yk_line_default);
}

void yk_line_innit(YK_Line *out)
{
    out->shader_program = yk_shader_create("yk-res/shaders/default/line.vert", "yk-res/shaders/default/line.frag");
    f4 vertices[] =
        {
            -0.5, 0.5f,
            0.5f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f

        };

    GLuint vbo;
    glGenVertexArrays(1, &out->vertex_arrays);
    glGenBuffers(1, &vbo);

    glBindVertexArray(out->vertex_arrays);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo);

    glUseProgram(out->shader_program);
}

void yk_renderer2d_render_line(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color *col)
{
    glUseProgram(yk_line_default.shader_program);
    glBindVertexArray(yk_line_default.vertex_arrays);

    u4 modelLoc = glGetUniformLocation(yk_line_default.shader_program, "model");
    u4 viewLoc = glGetUniformLocation(yk_line_default.shader_program, "view");
    u4 projectionLoc = glGetUniformLocation(yk_line_default.shader_program, "projection");
    u4 colorLoc = glGetUniformLocation(yk_line_default.shader_program, "color");

    {
        m4f out;
        out = yk_mat4f_identity();
        // Use a union and allow a transform3d to store this.
        // Other option is to have translate, rotate and scale for 2d
        yk_math_transform_translate(&out, &(v3f){transform->pos.x, transform->pos.y, -1.f});

        yk_math_transform_rotate(&out, transform->rot_z, &YK_WORLD_FORWARD);

        yk_math_transform_scale(&out, &(v3f){transform->scale.x, transform->scale.y, -1.f});

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &out.m00);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));
    glUniform4f(colorLoc, col->r, col->g, col->b, col->a);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
    draw_calls++;

    glBindVertexArray(0);
}

void yk_renderer2d_render_line_p(YK_Renderer2d *renderer, v2f pos, f4 rot, f4 thickness, YK_Color *col)
{
    glUseProgram(yk_line_default.shader_program);
    glBindVertexArray(yk_line_default.vertex_arrays);

    u4 modelLoc = glGetUniformLocation(yk_line_default.shader_program, "model");
    u4 viewLoc = glGetUniformLocation(yk_line_default.shader_program, "view");
    u4 projectionLoc = glGetUniformLocation(yk_line_default.shader_program, "projection");
    u4 colorLoc = glGetUniformLocation(yk_line_default.shader_program, "color");

    {
        m4f out;
        out = yk_mat4f_identity();
        // Use a union and allow a transform3d to store this.
        // Other option is to have translate, rotate and scale for 2d
        yk_math_transform_translate(&out, &(v3f){pos.x, pos.y, -1.f});

        yk_math_transform_rotate(&out, rot, &YK_WORLD_FORWARD);

        yk_math_transform_scale(&out, &(v3f){1.f, thickness, -1.f});

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &out.m00);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));
    glUniform4f(colorLoc, col->r, col->g, col->b, col->a);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
    draw_calls++;

    glBindVertexArray(0);
}

void yk_line_destroy(YK_Line *out)
{
    glDeleteVertexArrays(1, &(out->vertex_arrays));
    glDeleteProgram(out->shader_program);
}

void yk_renderer2d_render_rect(YK_Renderer2d *renderer, YK_Transform2d *transform, f4 thickness, YK_Color *col)
{
    v2f _pos = transform->pos;
    v2f _hscalex = {.y = transform->scale.x / 2, .x = 0.f};
    v2f _hscaley = {.x = transform->scale.y / 2, .y = 0.f};

    yk_renderer2d_render_line_p(renderer, yk_math_vec2f_add(&_pos, &_hscalex), 0.f, thickness, col);
    yk_renderer2d_render_line_p(renderer, yk_math_vec2f_sub(&_pos, &_hscalex), 0.f, thickness, col);
    yk_renderer2d_render_line_p(renderer, yk_math_vec2f_add(&_pos, &_hscaley), 90.f * DEG_TO_RAD, thickness, col);
    yk_renderer2d_render_line_p(renderer, yk_math_vec2f_sub(&_pos, &_hscaley), 90.f * DEG_TO_RAD, thickness, col);
}

void yk_renderer2d_render_quad(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color *col)
{
    yk_renderer2d_render_quad_sprite_z(renderer, transform, 1, col, &white_square);
}

void yk_renderer2d_render_quad_sprite(YK_Renderer2d *renderer, YK_Transform2d *transform, YK_Color *col, YK_Texture *texture)
{
    yk_renderer2d_render_quad_sprite_z(renderer, transform, 1, col, texture);
}

void yk_renderer2d_render_quad_z(YK_Renderer2d *renderer, YK_Transform2d *transform, f4 layer, YK_Color *col)
{
    yk_renderer2d_render_quad_sprite_z(renderer, transform, layer, col, &white_square);
}

#define MAX_LAYER (10.f)
#define I_MAX_LAYER (1.f / MAX_LAYER)

void yk_renderer2d_render_quad_sprite_z(YK_Renderer2d *renderer, YK_Transform2d *transform, f4 layer, YK_Color *col, YK_Texture *texture)
{
    glUseProgram(yk_rect_default.shader_program);
    glBindVertexArray(yk_rect_default.vertex_arrays);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    u4 modelLoc = glGetUniformLocation(yk_rect_default.shader_program, "model");
    u4 viewLoc = glGetUniformLocation(yk_rect_default.shader_program, "view");
    u4 projectionLoc = glGetUniformLocation(yk_rect_default.shader_program, "projection");
    u4 colorLoc = glGetUniformLocation(yk_rect_default.shader_program, "color");

    {
        m4f out;
        out = yk_mat4f_identity();
        // Use a union and allow a transform3d to store this.
        // Other option is to have translate, rotate and scale for 2d
        // YK_Transform _trans = {{transform->pos.x, transform->pos.y, -1.f}, {0.f, 0.f, transform->rot_z}, {transform->scale.x, transform->scale.y, 0.f}};

        yk_math_transform_translate(&out, &(v3f){transform->pos.x, transform->pos.y, (2.f * ((layer * I_MAX_LAYER) - 0.5f) * MAX_LAYER)});

        yk_math_transform_rotate(&out, transform->rot_z, &YK_WORLD_FORWARD);

        yk_math_transform_scale(&out, &(v3f){transform->scale.x, transform->scale.y, 0.f});

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &out.m00);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));

    glUniform4f(colorLoc, col->r, col->g, col->b, col->a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    draw_calls++;

    glBindVertexArray(0);
}