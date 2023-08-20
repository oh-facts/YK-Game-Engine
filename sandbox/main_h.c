#include <yk_app_h.h>

int main()
{
  YK_App_h app;
  yk_app_innit(&app);
  yk_app_run(&app);
  yk_app_quit(&app);

  return 0;
}
