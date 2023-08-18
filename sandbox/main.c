
#include <yk_app.h>
#include <yk_math.h>

/*
  To Do: 1. Rotations
         2. Testing api
         3. Logger
*/
int main()
{

  /*
  YK_Vec4f pos = {1,1,1,1};
  YK_Mat4f trans = yk_mat4f_scalar(1);
  trans = yk_transform_scale(&trans,&(YK_Vec3f){2,2,2});
  trans = yk_transform_translate(&trans,&(YK_Vec3f){1,2,3});
  pos = yk_math_mat4f_mul_vec4f(&trans,&pos);
  yk_vec4f_print_w(&pos);
 */

  /*
    YK_Vec3f vec1 = {2, 3, 4};
    YK_Vec3f vec2 = {5, -1, 0};
    YK_Vec3f cross = yk_math_vec3f_cross(&vec1,&vec2);
    yk_vec3f_print(&cross);

    f4 dot = yk_math_vec3f_dot(&vec1,&vec2);
    printf("%f",dot);

  */

  /*
   YK_Vec3f vec = {2, 3, 4};
   vec = yk_vec3f_normalize(&vec);
   yk_vec3f_print(&vec);
  */
  /*
  YK_Vec4f vec = {9.0f, 3.0f, 2.0f, 1.0f};

  YK_Mat4f trans = yk_mat4f_scalar(1.0f);
  trans = yk_transform_translate(&trans, &(YK_Vec3f){0.0f, 8.0f, 2.0f});
  vec = yk_math_mat4f_mul_vec4f(&trans, &vec);
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
