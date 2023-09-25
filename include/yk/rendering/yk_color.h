#ifndef YK_COLOR_H
#define YK_COLOR_H

#include <yk/math/yk_math_types.h>


struct YK_Color
{
    f4 r,g,b,a;
};


typedef struct YK_Color YK_Color;

#define YK_COLOR_RED       ((struct YK_Color){1.0f, 0.0f, 0.0f, 1.0f})
#define YK_COLOR_GREEN     ((struct YK_Color){0.0f, 1.0f, 0.0f, 1.0f})
#define YK_COLOR_BLUE      ((struct YK_Color){0.0f, 0.0f, 1.0f, 1.0f})
#define YK_COLOR_YELLOW    ((struct YK_Color){1.0f, 1.0f, 0.0f, 1.0f})
#define YK_COLOR_MAGENTA   ((struct YK_Color){1.0f, 0.0f, 1.0f, 1.0f})
#define YK_COLOR_CYAN      ((struct YK_Color){0.0f, 1.0f, 1.0f, 1.0f})
#define YK_COLOR_ORANGE    ((struct YK_Color){1.0f, 0.5f, 0.0f, 1.0f})
#define YK_COLOR_PURPLE    ((struct YK_Color){0.5f, 0.0f, 0.5f, 1.0f})
#define YK_COLOR_TEAL      ((struct YK_Color){0.0f, 0.5f, 0.5f, 1.0f})
#define YK_COLOR_GRAY      ((struct YK_Color){0.5f, 0.5f, 0.5f, 1.0f})

/*
enum YK_COLOR_TYPE
{
    YK_COLOR_RGBA,
    YK_COLOR_HEX,
};

typedef enum YK_COLOR_TYPE YK_COLOR_TYPE;


union YK_Color
{
    struct
    {
        f4 r, g, b;
    };

    struct
    {
        i4 hex;
    };

    i4 a;

    YK_COLOR_TYPE type;
    
};

typedef union YK_Color YK_Color;

void yk_color_normalized(YK_Color *out);
*/
#endif