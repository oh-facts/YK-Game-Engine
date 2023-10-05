#include <yk/rendering/yk_renderer2d.h>


struct YK_Rect
{
    GLuint shader_program;
    GLuint vertex_arrays;
};

typedef struct YK_Rect YK_Rect;

void yk_rect_innit(YK_Rect *out);
void yk_rect_destroy(YK_Rect *out);

YK_Yektor yk_rects;

YK_Texture white_square;

YK_Rect yk_rect_default;

i4 draw_calls;

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

void yk_renderer2d_render_rect(YK_Renderer2d *renderer,YK_Transform *transform, YK_Color *col)
{
    yk_renderer2d_render_rect_sprite(renderer, transform, col, &white_square);
}

void yk_renderer2d_render_rect_sprite(YK_Renderer2d *renderer, YK_Transform *transform, YK_Color *col, YK_Texture *texture)
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

        yk_math_transform_translate(&out, &transform->pos);

        v3f _rot = transform->rot;
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

void yk_rect_destroy(YK_Rect *out)
{
    glDeleteVertexArrays(1, &(out->vertex_arrays));
    glDeleteProgram(out->shader_program);
}

void yk_renderer2d_innit(YK_Renderer2d *ren, YK_Camera2d *current_cam, YK_Window *win)
{
    ren->current_cam = current_cam;
    ren->proj_mat = yk_camera2d_get_projection_matrix(current_cam, (f4)win->width / win->height);
    ren->view_mat = yk_camera2d_get_view_matrix(current_cam);

    white_square = yk_texture_create("yk-res/textures/white_square.png");

    yk_rect_innit(&yk_rect_default);

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

void yk_renderer2d_set_bg(f4 r, f4 g, f4 b, f4 a)
{
    glClearColor(r, g, b, a);
}

void yk_renderer2d_cleanup()
{
    yk_rect_destroy(&yk_rect_default);
}