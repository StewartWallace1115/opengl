#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "opengl_ults.h"
#include <iostream>
#include <math.h>
#include "Shader.h"

const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{   
    
   float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    };
    
    /*
    int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    */
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);
    GLFWwindow* window = myclass.createWindows(SCR_WIDTH,SCR_HEIGHT, "LearnOpenGL");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader(fragmentShaderSource);

    int programShader = myclass.linkShaders(vertexShader, fragmentShader);

    int vao = myclass.linkingAttributes(vertices, sizeof(vertices));

    //int vao = myclass.ElementBuffer(vertices, sizeof(vertices), indices, sizeof(indices));

    while (!glfwWindowShouldClose(window))
    {      
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        myclass.processInput(window, GLFW_KEY_ESCAPE);
        
        myclass.drawTriangle(programShader, vao);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}