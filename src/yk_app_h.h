#ifndef YK_APP_H_H
#define YK_APP_H_H

#include<yk_core_types.h>
#include <stdio.h>

typedef struct YK_App_h
{
    b1 isRunning;
    const char *_test;

} YK_App_h;


void yk_app_innit(YK_App_h *app);
void yk_app_run(YK_App_h *app);
void yk_app_quit(YK_App_h *app);

#endif