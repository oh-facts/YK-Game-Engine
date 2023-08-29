#ifndef YK_RENDERER_H
#define YK_RENDERER_H

#include <glad/glad.h>
#include <yk/yk_camera.h>
#include <yk/math/yk_math.h>

typedef enum YK_Render_object_type
{
    YK_RECT,
    YK_CUBE
}
YK_Render_object_type;

typedef struct YK_Render_object
{
    GLuint shaderProgram;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint index_count;
    GLuint vertex_count;
    GLuint texture;
    YK_Mat4f model_mat;
    YK_Vec3f pos;
    YK_Render_object_type type;

} YK_Render_object;

typedef struct YK_Renderer
{
    /*
        Current camera reference. Cameras are "owned" by the app. The
        app creates them and the renderer can choose which camera to render
        to.
    */
    YK_Camera *current_cam;

    YK_Mat4f view_mat;

    YK_Mat4f proj_mat;
} YK_Renderer;

GLuint yk_shader_create(const char *vertexFile, const char *fragmentFile);

YK_Render_object yk_render_object_create(YK_Render_object_type type, const char *imageFile);
void yk_render_object(YK_Renderer *renderer, YK_Render_object *obj);
void yk_render_object_destroy(YK_Render_object *obj);

void yk_render_object_set_pos(YK_Render_object *obj, YK_Vec3f *pos);
void yk_render_object_move(YK_Render_object *obj, YK_Vec3f *pos);

void yk_renderer_innit(YK_Renderer *renderer, YK_Camera *current_cam);
void yk_renderer_run(YK_Renderer *renderer, YK_Window *win);

#endif