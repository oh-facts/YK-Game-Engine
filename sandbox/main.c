#include <yk_app.h>

/*
  To Do: 1. Rotations
         2. Unit Testing api
         3. Logger
*/

int main()
{


  /*
  YK_Vec4f pos = {1, 0, 0, 1};
  YK_Mat4f trans = yk_mat4f_scalar(1);
  trans = yk_transform_scale(&trans, &(YK_Vec3f){0.5f, 0.5f, 0.5f});
  pos = yk_math_mat4f_mul_vec4f(&trans, &pos);

  trans = yk_transform_rotate(&trans, 90.f * DEG_TO_RAD, &(YK_Vec3f){0.0f, 0.0f, 1.f});
  pos = yk_math_mat4f_mul_vec4f(&trans, &pos);

  yk_vec4f_print(&pos);
*/
  /*
    YK_Vec4f pos = {1, 0, 0, 1};
    YK_Mat4f trans = yk_mat4f_scalar(1);
    trans = yk_transform_rotate(&trans, 90.f * DEG_TO_RAD, &(YK_Vec3f){0.0f, 0.0f, 1.f});
    YK_Mat4f trans2 = yk_mat4f_scalar(1);
    trans2 = yk_transform_scale(&trans2, &(YK_Vec3f){0.5f, 0.5f, 0.5f});

    YK_Mat4f trans_f = yk_math_mat4f_mul_mat4f(&trans,&trans2);

    pos = yk_math_mat4f_mul_vec4f(&trans_f, &pos);
    yk_vec4f_print(&pos);
    */
  
  YK_App app;
  yk_app_innit(&app);
  yk_app_run(&app);
  yk_app_quit(&app);
  
  return 0;
}

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
  printf("Vector 1: ");
  yk_vec3f_print(&vec1);
  printf("Vector 2: ");
  yk_vec3f_print(&vec2);

  YK_Vec3f cross = yk_math_vec3f_cross(&vec1, &vec2);
  printf("Cross product: ");
  yk_vec3f_print(&cross);

  f4 dot = yk_math_vec3f_dot(&vec1, &vec2);
  printf("dot product: ");
  printf("%f", dot);
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
