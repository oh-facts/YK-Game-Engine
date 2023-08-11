#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

namespace AE
{
    namespace util
    {
        std::string getFileContents(const char* filename);

    }
} // namespace AE

#endif