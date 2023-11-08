#include <yk/yk_app.h>
#include <glad/glad.h>
#define NUM (100000)

#define SIM_SPEED (1.f)
#define ROT_SPEED (1.0f)

struct entity
{
  YK_Transform2d transform;
};

typedef struct viq
{
  u4 shader_program;
  u4 vertex_arrays;
  u4 ivbo;
} viq;

viq iq;
typedef struct entity entity;

entity *squares;

void draw_normal(YK_Renderer2d *ren2d);
void update_player(entity *py, f4 delta);
#define SPEED 4

void init_instanced(m4f model[]);

void draw_instanced(YK_Renderer2d *ren2d, m4f model[]);

int main()
{
  squares = malloc(sizeof(entity) * NUM);
  // YK_Window *win = yk_window_create("this is a title", 960, 540);
  YK_Window *win = yk_window_create_default();
  yk_window_set_vsync(win, false);

  YK_Camera2d cam2d;
  yk_camera2d_innit(&cam2d);
  cam2d.zoom = 1.f;

  YK_Renderer2d ren2d;
  yk_renderer2d_innit(&ren2d, &cam2d, win);

  f4 delta_time = 0.f;
  f4 last_frame = 0.f;

  yk_renderer2d_set_bg(0.2f, 0.3f, 0.3f, 1.f);

  entity py = {.transform = {{0, 0}, 0, {1.f, 1.f}}};

  // yk_renderer2d_set_bg(0.5f, 0.2f, 0.4f, 1.f);

  yk_renderer2d_set_bg(0.f, 0.f, 0.f, 1.f);

  m4f *poss = malloc(sizeof(m4f) * NUM);

  for (int i = 0; i < NUM; i++)
  {
    f4 r1_x = ((f4)rand() / RAND_MAX) * 20.0f - 10.f;
    f4 r1_y = ((f4)rand() / RAND_MAX) * 10.0f - 5.f;
    f4 r2 = ((f4)rand() / RAND_MAX) * 90.0f;
    f4 r3 = ((f4)rand() / RAND_MAX) * 0.5f + 0.2f;
    YK_Transform2d trans = {{r1_x, r1_y}, r2, {r3, r3}};
    squares[i].transform = trans;

    m4f out;
    out = yk_mat4f_identity();

    yk_math_transform_translate(&out, &(v3f){r1_x, r1_y, 0.f});
    yk_math_transform_rotate(&out, r2, &YK_WORLD_FORWARD);
    yk_math_transform_scale(&out, &(v3f){r3, r3, 0.f});
    // yk_mat4f_print(&out);

    poss[i] = out;
  }

  YK_Texture test = yk_texture_create("yk-res/textures/yk.png");
  YK_Texture test2 = yk_texture_create("yk-res/textures/default.jpg");

  i4 frame_count = 0;
  f4 total_elapsed_time = 0.f;

  init_instanced(poss);

  while (yk_window_is_running(win))
  {

    f4 current_frame = yk_get_time();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    frame_count++;
    total_elapsed_time += delta_time;

    // debug_input(&cam2d, delta_time);

    // update_player(&py, delta_time);
    yk_camera2d_debug_control(&cam2d, SPEED * delta_time);

    yk_renderer2d_begin_draw(&ren2d, win);
    // yk_renderer2d_render_quad_sprite_z(&ren2d, &py.transform, -8.f, &YK_COLOR_WHITE, &test2);

    draw_normal(&ren2d);

    //draw_instanced(&ren2d, poss);

    if (yk_input_is_key_tapped(YK_KEY_ENTER))
    {
      printf("Diagnostics \n");
      printf("----------- \n");
      printf("Draw Calls: %d\n", draw_calls);
      f4 average_frame_rate = frame_count / total_elapsed_time;

      printf("Current Frame Rate: %.0f FPS\n", 1.0 / delta_time);
      printf("Average Frame Rate: %.0f FPS\n", average_frame_rate);

      printf("Current Frame Time: %.2f ms\n", delta_time * 1000.0);
      printf("Average Frame Time: %.2f ms\n", (total_elapsed_time / frame_count) * 1000.0);
      printf("\n");
    }

    yk_window_update(win);
  }

  yk_renderer2d_destroy();
  yk_window_destroy(win);

  return 0;
}

void draw_normal(YK_Renderer2d *ren2d)
{
  for (int i = 0; i < NUM; i++)
  {
    f4 timeValue = (yk_get_time() + i * 0.1f) * SIM_SPEED;
    f4 r = sin(timeValue) / 2.0f + 0.5f;
    f4 g = sin(timeValue + 2.0f) / 2.0f + 0.5f;
    f4 b = sin(timeValue + 4.0f) / 2.0f + 0.5f;

    squares[i].transform.rot_z = timeValue * ROT_SPEED;
    yk_renderer2d_render_quad_z(ren2d, &squares[i].transform, -9.f, &(YK_Color){r, g, b, 1.f});
  }
}

void init_instanced(m4f model[])
{
  for (int i = 0; i < NUM; i++)
  {
    // yk_vec2f_print(&pos[i]);
  }
  glGenBuffers(1, &iq.ivbo);
  glBindBuffer(GL_ARRAY_BUFFER, iq.ivbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m4f) * NUM, &model[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  iq.shader_program = yk_shader_program_create_vertex_fragment("yk-res/shaders/instanced/rect.vert", "yk-res/shaders/instanced/rect.frag");

  f4 vertices[] = {
      -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
      0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
      -0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

      -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
      0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
      0.05f, 0.05f, 0.0f, 1.0f, 1.0f};

  GLuint vbo;
  glGenVertexArrays(1, &iq.vertex_arrays);
  glGenBuffers(1, &vbo);

  glBindVertexArray(iq.vertex_arrays);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // pos attrib
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

  // texture attrib
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

  // instanced attrib

  glBindBuffer(GL_ARRAY_BUFFER, iq.ivbo);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void *)(0));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void *)(1 * 4 * sizeof(float)));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void *)(2 * 4 * sizeof(float)));

  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void *)(3 * 4 * sizeof(float)));

  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vbo);

  glUseProgram(iq.shader_program);
}

void draw_instanced(YK_Renderer2d *ren2d, m4f model[])
{

  for (int i = 0; i < NUM; i++)
  {
    f4 timeValue = (yk_get_time() + i * 0.1f) * SIM_SPEED;
    f4 r = sin(timeValue) / 2.0f + 0.5f;
    f4 g = sin(timeValue + 2.0f) / 2.0f + 0.5f;
    f4 b = sin(timeValue + 4.0f) / 2.0f + 0.5f;

    yk_math_transform_rotate(&model[i], timeValue, &YK_WORLD_FORWARD);

    // yk_mat4f_print(&out);

    // poss[i] = out;
  }
  glBindBuffer(GL_ARRAY_BUFFER, iq.ivbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m4f) * NUM, &model[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glUseProgram(iq.shader_program);
  glBindVertexArray(iq.vertex_arrays);

  // u4 modelLoc = glGetUniformLocation(iq.shader_program, "model");
  u4 viewLoc = glGetUniformLocation(iq.shader_program, "view");
  u4 projectionLoc = glGetUniformLocation(iq.shader_program, "projection");

  {
    GLuint ivbo;
    glGenBuffers(1, &ivbo);
    glBindBuffer(GL_ARRAY_BUFFER, ivbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m4f) * NUM, &model[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(ren2d->view_mat.m00));
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &(ren2d->proj_mat.m00));

  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, NUM);
  draw_calls++;

  glBindVertexArray(0);
  glUseProgram(0);
}

void prepare_instanced(YK_Transform2d *trans)
{
}

void update_player(entity *py, f4 delta)
{
  v2f mv = {0, 0};

  if (yk_input_is_key_held(YK_KEY_W))
  {
    mv.y = SPEED;
  }

  if (yk_input_is_key_held(YK_KEY_A))
  {
    mv.x = -SPEED;
  }

  if (yk_input_is_key_held(YK_KEY_S))
  {
    mv.y = -SPEED;
  }

  if (yk_input_is_key_held(YK_KEY_D))
  {
    mv.x = SPEED;
  }

  py->transform.pos.x += mv.x * delta;
  py->transform.pos.y += mv.y * delta;
}
