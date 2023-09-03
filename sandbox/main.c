#include <yk/yk_app.h>

/*
  To Do: 1. Rotations
         2. Unit Testing api
         3. Logger
*/
typedef struct YK_Position_component
{
  float x, y;
} YK_Position_component;

YK_Yektor *pos_comps;

void yk_ecs_gravity_system()
{
  for (int i = 0; i < 10; i++)
  {
    (*(YK_Position_component *)yk_yektor_at(pos_comps, i)).y--;
  }
}

int main()
{
  /*
  YK_App app;
  yk_app_innit(&app);
  yk_app_run(&app);
  yk_app_quit(&app);
*/
  pos_comps = yk_yektor_innit(10, sizeof(YK_Position_component));
  YK_Position_component pos1 = {0.5f, 0.5f};
  yk_yektor_push(pos_comps, &pos1);
  YK_Position_component x = *(YK_Position_component *)yk_yektor_at(pos_comps, 0);

  printf("%f", x.x);

  return 0;
}