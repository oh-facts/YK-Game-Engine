#ifndef APP_H
#define APP_H

#include <Window.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct App
{
    Window m_win;

} App;


void innit(App *app);
void run(App *app);
void quit(App *app);

#endif
