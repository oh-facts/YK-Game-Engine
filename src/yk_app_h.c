#include <yk/yk_app_h.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

int kbhit_()
{
#ifdef _WIN32
    return _kbhit(); // Windows
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
#endif
}

volatile int g_interrupted = 0;

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_interrupted = 1;
    }
}

void yk_app_innit(YK_App_h *app)
{
    app->_test = "So no head?";
    app->isRunning = true;
    signal(SIGINT, signal_handler);
}
void yk_app_run(YK_App_h *app)
{
    printf("App is currently running. \nEnter q to quit.\n");

    while (app->isRunning && !g_interrupted)
    {
        if (kbhit_())
        {
            int key = getchar();
            if (key == 'q' || key == 'Q')
            {
                app->isRunning = 0;
            }
        }
    }
}
void yk_app_quit(YK_App_h *app)
{
    printf("App has quit \n");
}