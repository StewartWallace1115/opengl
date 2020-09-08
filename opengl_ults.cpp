#include "opengl_ults.h"
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void errorCallback(int id, const char* message) {
    std::cout << "Failed to create GLFW window" << std::endl;
}

bool Opengl_ults::init() 
{
    glfwSetErrorCallback(errorCallback);
    return glfwInit();
}
 

void Opengl_ults::setupWindows(int major, int minor) 
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* Opengl_ults::createWindows(int width, int height, const char* windowTitle) 
{
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}


void Opengl_ults::processInput(GLFWwindow *window, int key)
{
    if(glfwGetKey(window, key) == GLFW_PRESS)
        closeWindow(window);
}

void Opengl_ults::closeWindow(GLFWwindow *window)
{
    glfwSetWindowShouldClose(window, true);
}

bool Opengl_ults::createShader()
{
    return true;
}

int Opengl_ults::createVertexShader()
{

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if(vertexShader == 0)
    {
        errorCallback(0, ""); 
        return 0;
    }

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success; 
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        errorCallback(0, ""); 
        return 0;
    }
    return vertexShader;
}

int Opengl_ults::createFragmentShader(const char *fragmentShaderSource)
{
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(fragmentShader == 0)
    {
        errorCallback(0, ""); 
        return 0;
    }
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success; 
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        errorCallback(0, ""); 
        return 0;
    }
    return fragmentShader;
}

int Opengl_ults::linkShaders(int vertexShader, int fragementShader)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragementShader);
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
    glDeleteShader(fragementShader);
    return shaderProgram;
}

int Opengl_ults::linkingAttributes(float vertices[], int verticesSize)
{
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    ///glBindVertexArray(0);
    return VAO;
}

int Opengl_ults::linkElementBuffer(int indices[], int indicesSize)
{
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    return EBO;

}


int Opengl_ults::ElementBuffer(float vertices[], int verticesSize, int indices[], int indicesSize)
{
 unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    return VAO;
}

bool Opengl_ults::setupVertices(int programShader)
{
    return true;
}

void Opengl_ults::drawTriangle(int programShader, int VAO)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(programShader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Opengl_ults::drawSquare(int programShader, int VAO)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(programShader);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

