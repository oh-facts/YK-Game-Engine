#include <yk/yk_app.h>

int main()
{
    YK_Yektor testis;
    yk_yektor_innit(&testis, 5, sizeof(v2f));

    v2f pos = {4,4};

    yk_yektor_push(&testis,&pos);

    yk_yektor_print(&testis);
    return 0;
}