#include <yk/yk_texture.h>

YK_Texture yk_texture_create(const char *path)
{
    YK_Texture out;

    int numColCh;
    unsigned char *data;
    stbi_set_flip_vertically_on_load(1);
    data = stbi_load(path, &out.width, &out.height, &numColCh, 0);

    if (data)
    {
        if (numColCh == 3)
        {
            out.format = GL_RGB;
        }
        else if (numColCh == 4)
        {
            out.format = GL_RGBA;
        }
        else
        {
            stbi_image_free(data);
            printf("Image not loaded correctly.");
        }
    }

    glGenTextures(1, &out.id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, out.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, out.format , out.width, out.height, 0, out.format , GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return out;
}