#include <yk/rendering/yk_shader.h>
#include <glad/glad.h>

void yk_check_compile_errors(GLuint shader, const char *type);
void yk_check_link_errors(GLuint shader, const char *type);

i4 yk_shader_create(const char *vertexFile, const char *fragmentFile)
{

    const char *vertexShaderSource = yk_file_reader(vertexFile);
    const char *fragmentShaderSource = yk_file_reader(fragmentFile);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    yk_check_compile_errors(vertexShader, "Vertex Shader");

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    yk_check_compile_errors(fragmentShader, "Fragment Shader");

    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program, vertexShader);
    glAttachShader(shader_program, fragmentShader);
    glLinkProgram(shader_program);
    yk_check_link_errors(shader_program, "Shader Program");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader_program;
}

void yk_check_compile_errors(GLuint shader, const char *type)
{
    int success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        printf("ERROR::SHADER_COMPILATION_ERROR of type: %s \n %s \n", type, infoLog);
    }
}

void yk_check_link_errors(GLuint shader, const char *type)
{
    int success;
    char infoLog[1024];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        printf("ERROR::PROGRAM_LINKING_ERROR of type: %s \n %s \n", type, infoLog);
    }
}