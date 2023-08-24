#include <yk/yk_file_reader.h>

/*
fopen_s() is only defined in windows
*/
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif

char *yk_file_reader(const char *filename)
{
    FILE *file;
    fopen_s(&file,filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Unable to open the file %s\n",filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length == 0)
    {
        fprintf(stderr, "Error: File is empty\n");
        fclose(file);
        return NULL;
    }

    char *string = malloc(sizeof(char) * (length + 1));

    char c;
    int i = 0;

    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    fclose(file);

    return string;
}