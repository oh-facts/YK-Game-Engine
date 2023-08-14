
#include <yk_app.h>


int main()
{
  YK_App app;
  yk_app_innit(&app);
  yk_app_run(&app);
  yk_app_quit(&app);
  
  return 0;
}
