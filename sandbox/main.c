#include <yk/yk_app.h>

/*
  To Do: 1. Rotations
         2. Unit Testing api
         3. Logger
*/

int main()
{
  YK_App app;
  yk_app_innit(&app);
  yk_app_run(&app);
  yk_app_quit(&app);
  return 0;
}