#include <stdio.h>
#ifdef _WIN32
//pass
#else
#include <unistd.h>
#endif



int main()
{
    printf("This is an example service. This does nothing, because it is an (a bad)example \n");

    sleep(4);

    printf("Service quitting\n");

    return 0;
}