#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);
    int vertexShader = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    int fragmentShader = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    ID = linkShaderProgram(vertexShader, fragmentShader);
}

std::string Shader::readFile(const char* filePath)
{
    std::ifstream file(filePath);
    if(file.fail())
    {
        std::cerr << "failed to open file" << std::endl;
        return NULL;
    }

    return std::string ((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
}

void errorCallback(int id, const char* message)
{
    std::cout << "Failed to create GLFW window" << std::endl;
}

int compileShader(const char *shaderSource, unsigned int shaderType)
{
    int shader = glCreateShader(shaderType);
    if(shader == 0)
    {
        errorCallback(0, ""); 
        return 0;
    }
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int success; 
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        errorCallback(0, ""); 
        return 0;
    }
    return shader;
}

int linkShaderProgram(int vertexShader, int fragmentShader)
{
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success; 
    char infoLog[512];
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        errorCallback(0, ""); 
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}