
#include <yk_app.h>
#include <yk_math.h>

int main()
{

  YK_Vec3f vec = {2, 3, 4};
  vec = yk_vec3f_normalize(&vec);
  yk_vec3f_print(&vec);

  /*
  YK_Vec4f vec = {9.0f, 3.0f, 2.0f, 1.0f};

  YK_Mat4f trans = yk_mat4f_scalar(1.0f);
  trans = yk_mat4f_translate(&trans, &(YK_Vec3f){0.0f, 8.0f, 2.0f});
  vec = yk_math_mul_mat4f_vec4f(&trans, &vec);
  printf("%.f %.f %.f\n", vec.x, vec.y, vec.z);
  */

  /*
    YK_App app;
    yk_app_innit(&app);
    yk_app_run(&app);
    yk_app_quit(&app);
  */

  return 0;
}
