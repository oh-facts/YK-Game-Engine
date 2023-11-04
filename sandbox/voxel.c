#include <yk/yk_app.h>
#include <glad/glad.h>

u4 shader;

void voxel_renderer_init()
{
    shader = yk_shader_create("yk-res/shaders/default/voxel.vert", "yk-res/shaders/default/voxel.frag");

    glUseProgram(shader);
}

void voxel_renderer_update()
{
    v3f a = {0, 0, 1};
    v3f b = {0, 0, -1};
    v3f c = {0, 0, 0};

    glUniform3fv(glGetUniformLocation(shader, "cameraPosition"), 1, &a.x);
    glUniform3fv(glGetUniformLocation(shader, "rayDirection"), 1, &b.x);
    glUniform3fv(glGetUniformLocation(shader, "voxelPosition"), 1, &c.x);
    glUseProgram(shader);
}

int main()
{
    YK_Window *win = yk_window_create_default();

    voxel_renderer_init();

    while (yk_window_is_running(win))
    {
        glClear(GL_COLOR_BUFFER_BIT);
       // voxel_renderer_update();
        yk_window_update(win);
    }

    return 0;
}