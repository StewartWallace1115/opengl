#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
class Opengl_ults{

    public: bool init();
            void setupWindows(int major, int minor);
            GLFWwindow* createWindows(int height, int weight, const char* windowTitle);
            void processInput(GLFWwindow *window, int key);
            void closeWindow(GLFWwindow *window);
            bool createShader();
            int createVertexShader();
            int createFragmentShader(const char *fragmentShaderSource);
            int linkShaders(int vertexShader, int fragementShader);
            bool setupVertices(int programShader);
            int linkingAttributes(float vertics[], int verticesSize);
            void drawTriangle(int programShader, int VAO);
            void drawSquare(int programShader, int VAO);
            int linkElementBuffer(int indices[], int indicesSize);
            int ElementBuffer(float vertices[], int verticesSize,int indices[], int indicesSize);
            static std::string errorMessageDisplay;
};