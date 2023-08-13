#ifndef YK_APP_H
#define YK_APP_H

#include <yk_window.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct YK_App
{
    YK_Window m_win;

} YK_App;


void yk_app_innit(YK_App *app);
void yk_app_run(YK_App *app);
void yk_app_quit(YK_App *app);

#endif
