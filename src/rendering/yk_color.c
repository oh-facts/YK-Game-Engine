#include <yk/rendering/yk_color.h>


/*
void yk_color_normalized(YK_Color *out)
{
    switch (out->type)
    {
    case YK_COLOR_RGBA:
        out->r /= 255;
        out->g /= 255;
        out->b /= 255;
        out->a /= 255;
        break;

    case YK_COLOR_HEX:

        out->r = ((out->hex >> 16) & 0xFF) / 255;
        out->g = ((out->hex >> 16) & 0xFF) / 255;
        out->b = ((out->hex >> 16) & 0xFF) / 255;
        out->a /= 255;

    default:
        break;
    }
}
*/