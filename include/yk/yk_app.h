#ifndef YK_APP_H
#define YK_APP_H

#include <yk/yk_defines.h>
#include <yk/yk_window.h>
#include <yk/math/yk_math.h>
#include <stdio.h>
#include <stdlib.h>
#include <yk/ecs/yk_ecs.h>
#include <yk/data_structures/yk_yektor.h>
#include <yk/yk_scene.h>

#include <yk/yk_renderer2d.h>
#include <yk/yk_camera2d.h>

typedef struct YK_App
{
    YK_Window m_win;
    YK_Renderer2d m_ren;
    YK_Scene m_scene;

    f4 delta_time;
    f4 last_frame;
} YK_App;

YK_API void yk_app_innit(YK_App *app);
YK_API void yk_app_run(YK_App *app);
YK_API void yk_app_quit(YK_App *app);

YK_API void yk_app_is_running(YK_App *app);

#endif
