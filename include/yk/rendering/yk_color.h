#ifndef YK_COLOR_H
#define YK_COLOR_H

#include <yk/math/yk_math_types.h>


#define YK_COLOR_RED              ((struct YK_Color){1.0f, 0.0f, 0.0f, 1.0f})
#define YK_COLOR_GREEN            ((struct YK_Color){0.0f, 1.0f, 0.0f, 1.0f})
#define YK_COLOR_BLUE             ((struct YK_Color){0.0f, 0.0f, 1.0f, 1.0f})
#define YK_COLOR_YELLOW           ((struct YK_Color){1.0f, 1.0f, 0.0f, 1.0f})
#define YK_COLOR_MAGENTA          ((struct YK_Color){1.0f, 0.0f, 1.0f, 1.0f})
#define YK_COLOR_CYAN             ((struct YK_Color){0.0f, 1.0f, 1.0f, 1.0f})
#define YK_COLOR_ORANGE           ((struct YK_Color){1.0f, 0.5f, 0.0f, 1.0f})
#define YK_COLOR_PURPLE           ((struct YK_Color){0.5f, 0.0f, 0.5f, 1.0f})
#define YK_COLOR_TEAL             ((struct YK_Color){0.0f, 0.5f, 0.5f, 1.0f})
#define YK_COLOR_GRAY             ((struct YK_Color){0.5f, 0.5f, 0.5f, 1.0f})
#define YK_COLOR_WHITE            ((struct YK_Color){1.0f, 1.0f, 1.0f, 1.0f})
#define YK_COLOR_TRANSPARENT      ((struct YK_Color){0.0f, 0.0f, 0.0f, 0.0f})

/*
    N: r,g,b,a normalized range.
    
*/
enum YK_COLOR_TYPE
{
    YK_COLOR_N,
    YK_COLOR_RGBA,
    YK_COLOR_HEX,
};

typedef enum YK_COLOR_TYPE YK_COLOR_TYPE;

/* 
    stores color
    as rgb or hex
    transparency in a
    color needs to be normalized before sending it to functions that accept color
*/
struct YK_Color
{
    union
    {
        struct
        {
           f4 r,g,b;
        };
        
        f4 hex;
        
    };

    f4 a;

    YK_COLOR_TYPE type;
    
};

typedef struct YK_Color YK_Color;

#define NORMALIZE_RGBA(color) do { \
    (color).r = (color).r / 255.0; \
    (color).g = (color).g / 255.0; \
    (color).b = (color).b / 255.0; \
} while (0)

#define NORMALIZE_HEX

//void yk_color_normalized(YK_Color *out);

#endif