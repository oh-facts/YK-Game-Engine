#ifndef YK_FILE_READER_H
#define YK_FILE_READER_H

#include <stdio.h>
#include <stdlib.h>


/*
    Reads a file at filepath and retuns data as a char *
    The returned char* needs to be freed by the caller.
*/
char *yk_file_reader(const char *filepath);



#endif