#include <Renderer.hpp>
#include <FileReader.hpp>

namespace AE
{
     unsigned int create_shader(const char *vertexFile, const char *fragmentFile){
        std::string vertexShaderSourceStr = util::getFileContents("res\\default.vert");
        const char *vertexShaderSource = vertexShaderSourceStr.c_str();

        std::string fragmentShaderSourceStr = util::getFileContents("res\\default.frag");
        const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        
        unsigned int shader_program = glCreateProgram();

        glAttachShader(shader_program, vertexShader);
        glAttachShader(shader_program, fragmentShader);
        glLinkProgram(shader_program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shader_program;
    }
} // namespace AE
