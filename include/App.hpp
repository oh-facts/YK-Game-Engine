#ifndef APP_HPP
#define APP_HPP

#include <Window.hpp>

namespace AE
{

    struct App
    {
        void innit();
        void run();
        void quit();

        Window m_win;
    };
}

#endif
