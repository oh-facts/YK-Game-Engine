#include <yk/rendering/yk_renderer.h>
#include <stb/stb_image.h>

YK_Render_object yk_render_object_create(YK_Render_object_type type, const char *imageFile)
{
    YK_Render_object out;
    out.type = type;

    if (type == YK_RECT)
    {
        out.shaderProgram = yk_shader_create("yk-res/shaders/default.vert", "yk-res/shaders/default.frag");
        float vertices[] =
            {
                // Position           // Color                  // Texture Coords
                0.5f, 0.5f, 0.0f, 1.0f, 0.875f, 0.0f, 1.0f, 1.0f,      // top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.564f, 0.784f, 1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f, 1.0f, 0.875f, 0.0f, 0.0f, 0.0f,    // bottom left
                -0.5f, 0.5f, 0.0f, 0.129f, 0.329f, 0.647f, 0.0f, 1.0f, // top left
            };

        unsigned int indices[] =
            {
                0, 1, 3,
                1, 2, 3
            };
        out.vertex_count = 4;
        out.index_count = 6;

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

    }
    else if (type == YK_CUBE)
    {
        out.pos.x = 0.f;
        out.pos.y = 0.f;
        out.pos.z = 0.f;
        out.model_mat = yk_mat4f_identity();

        out.shaderProgram = yk_shader_create("yk-res/shaders/cube/default.vert", "yk-res/shaders/cube/default.frag");
        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

        out.vertex_count = 36;
        out.index_count = 0;

        glGenVertexArrays(1, &out.vao);
        glGenBuffers(1, &out.vbo);

        glBindVertexArray(out.vao);

        glBindBuffer(GL_ARRAY_BUFFER, out.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
    }
    else
    {
        printf("Invalid type");
        //crash or something
    }
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

void yk_render_object(YK_Renderer *renderer, YK_Render_object *obj)
{
    u4 modelLoc = glGetUniformLocation(obj->shaderProgram, "model");
    u4 viewLoc = glGetUniformLocation(obj->shaderProgram, "view");
    u4 projectionLoc = glGetUniformLocation(obj->shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(obj->model_mat.m00));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(renderer->view_mat.m00));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(renderer->proj_mat.m00));

    glUseProgram(obj->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, obj->texture);

    glBindVertexArray(obj->vao);

    if (obj->index_count>0)
    {
        glDrawElements(GL_TRIANGLES, obj->index_count, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, obj->vertex_count);
    }
}

void yk_render_object_destroy(YK_Render_object *obj)
{
    glDeleteVertexArrays(1, &(obj->vao));
    glDeleteBuffers(1, &(obj->vbo));
    glDeleteBuffers(1, &(obj->ebo));

    glDeleteTextures(1, &(obj->texture));

    glDeleteProgram(obj->shaderProgram);
}

void yk_render_object_set_pos(YK_Render_object *obj, YK_Vec3f *pos)
{
    obj->model_mat = yk_mat4f_identity();
    yk_maths_transform_translate(&obj->model_mat, pos);
}

void yk_render_object_move(YK_Render_object *obj, YK_Vec3f *pos)
{
    yk_maths_transform_translate(&obj->model_mat, pos);
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
        renderer->view_mat = yk_look_at(&cam->pos, &_temp, &YK_WORLD_UP);
    }

    renderer->proj_mat = yk_mat4f_identity();

    f4 _aspect_ratio = (f4)win->width/win->height;

    if(cam->type == YK_CAMERA_TYPE_P)
    {
        renderer->proj_mat = yk_mat4f_perspective(cam->fov * DEG_TO_RAD, _aspect_ratio, 0.1f, 100.f);
    }
    else
    {
        float _zoom = cam->fov*.01f;
        renderer->proj_mat = yk_mat4f_ortho(-_aspect_ratio * _zoom, _aspect_ratio*_zoom, -_zoom, _zoom, 2.f, 100.f);
    }
   
}