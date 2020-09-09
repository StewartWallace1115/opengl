#include "Unity/src/unity.h"
#include <iostream>
#include <sstream>
#include "opengl_ults.h"
#include "string.h"
#include "unistd.h"


std::stringstream buffer1;
std::streambuf * old1;

float triangleVertices [] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f, 0.5f, 0.0f, 
    };

float squareVertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
int squareIndices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.1f, 0.1f, 1.0f);\n"

    "}\n\0";

const char *fragmentShaderSourceFail = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "oid main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.1f, 0.1f, 1.0f);\n"

    "}\n\0";

void setupOpenGLUtls(Opengl_ults* myclass)
{
    //Opengl_ults myclass;
    myclass->init();
    myclass->setupWindows(3,3);

    old1 = std::cout.rdbuf(buffer1.rdbuf());
  
    GLFWwindow* window = myclass->createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

const char* cleanup()
{
    std::string text = buffer1.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.flush();

    std::cout.rdbuf(old1);
    std::cout.flush();
    return array;
}


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_should_init_successfully(void) {
    Opengl_ults myclass;
    bool result = myclass.init();
    TEST_ASSERT_TRUE(result);
    glfwTerminate();
}

void test_should_init_unsuccessfully(void) 
{
    // Don't know how to test yet.

}

void test_should_setup_windows_successfully(void) 
{
    Opengl_ults myclass;
    bool result = myclass.init();
    myclass.setupWindows(3,3);

    // Redirect std output stream
    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    myclass.createWindows(300, 300, "LearnOpenGL");
    glfwTerminate();

    std::string text = buffer.str(); 
    std::cout << text;
    // Reset buffer
    std::cout.rdbuf(old);
    const char *array = text.c_str();
    TEST_ASSERT_EQUAL_STRING(array, "");  
    glfwTerminate(); 
}

void test_should_setup_windows_unsuccessfully(void) 
{
    Opengl_ults myclass;
    bool result = myclass.init();
    myclass.setupWindows(4,3);

    // Redirect std output stream
    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    myclass.createWindows(300, 300, "LearnOpenGL");

    std::string text = buffer.str(); 
    // Reset buffer
    std::cout.rdbuf(old);
    const char *array = text.c_str();
    
    TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\n");    
}

void test_should_create_window(void) 
{
    Opengl_ults myclass;
    bool result = myclass.init();
    myclass.setupWindows(3,3);

    // Redirect std output stream
    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    std::string text = buffer.str(); 
    // Reset buffer
    std::cout.rdbuf(old);

    const char *array = text.c_str();
    TEST_ASSERT_EQUAL_STRING(array, "");  
    TEST_ASSERT_NOT_NULL(window);
    glfwTerminate();
}

void test_should_fail_to_create_window(void)
{

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

    Opengl_ults myclass;
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    std::string text = buffer.str(); 
    const char *array = text.c_str();
    TEST_ASSERT_NULL(window);
    TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\n");  

    // Reset buffer
    std::cout.rdbuf(old);
}

void test_should_close_window_succesffully(void) 
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    
    myclass.closeWindow(window);
    bool result = glfwWindowShouldClose(window);
    TEST_ASSERT_TRUE(result);
    glfwTerminate();
}

void test_should_fail_vertex_shader(void)
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  

    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    bool result = myclass.createVertexShader();
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    //TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\n");  
    //TEST_ASSERT_FALSE(result);
    TEST_IGNORE_MESSAGE("To cause test to fail mess up syntax of vertex src or pass vertex shader incorrect shader type");
}

void test_should_create_vertex_shader(void)
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    bool result = myclass.createVertexShader();
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    TEST_ASSERT_EQUAL_STRING(array, "");  
    TEST_ASSERT_TRUE(result);
}

void test_should_fail_fragment_shader(void)
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    bool result = myclass.createFragmentShader(fragmentShaderSourceFail);
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\n");  
    TEST_ASSERT_FALSE(result);
}

void test_should_create_fragment_shader(void)
{
    Opengl_ults myclass;
    const char* array;
    int result;

    setupOpenGLUtls(&myclass);
    result = myclass.createFragmentShader(fragmentShaderSource);
    array = cleanup();

    TEST_ASSERT_EQUAL_STRING(array, "");  
    TEST_ASSERT_NOT_EQUAL(result,0);
}

void test_should_fail_shader_linking(void)
{
    Opengl_ults myclass;
    const char* array;

    setupOpenGLUtls(&myclass);
    int frag = myclass.createFragmentShader(fragmentShaderSourceFail);
    int vertexShader = myclass.createVertexShader();

    int shaderProgram = myclass.linkShaders(vertexShader, frag);
    array = cleanup();

    //TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\nFailed to create GLFW window\n");  
    //TEST_ASSERT_EQUAL(0, shaderProgram);
    TEST_IGNORE_MESSAGE("Trying to figure out how to fail");
}

void test_should_link_shaders(void)
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader(fragmentShaderSource);
    int shaderProgram = myclass.linkShaders(vertexShader, fragmentShader);
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    TEST_ASSERT_EQUAL_STRING(array, "");  
    TEST_ASSERT_NOT_EQUAL(shaderProgram, 0);
}

void test_should_fail_link_vertex_attributes(void)
{
    
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader(fragmentShaderSource);
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    bool result = myclass.linkingAttributes(triangleVertices, sizeof(triangleVertices));
       std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);

    //TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\n");  
    //TEST_ASSERT_FALSE(result);
    TEST_IGNORE_MESSAGE("Trying to figure out to get test to fail");
}

void test_should_link_vertex_attributes(void)
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader(fragmentShaderSource);
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    bool result = myclass.linkingAttributes(triangleVertices, sizeof(triangleVertices));
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);

    TEST_ASSERT_EQUAL_STRING(array, "");  
    //TEST_ASSERT_TRUE(result);
}



void test_should_draw_triangle()
{
    
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader(fragmentShaderSource);
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    int vao = myclass.linkingAttributes(triangleVertices, sizeof(triangleVertices));
    myclass.drawTriangle(programShader, vao);
    
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);

    TEST_ASSERT_EQUAL_STRING(array, "");  
    //TEST_ASSERT_TRUE(result);

}

void test_should_draw_square()
{
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    GLFWwindow* window = myclass.createWindows(300, 300, "LearnOpenGL");
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader(fragmentShaderSource);
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    int vao = myclass.linkingAttributes(squareVertices, sizeof(squareVertices));
    int ebo = myclass.linkElementBuffer(squareIndices, sizeof(squareIndices));
    myclass.drawSquare(programShader, vao);
    
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    TEST_ASSERT_EQUAL_STRING(array, "");  
    //TEST_ASSERT_TRUE(result);

}


// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_should_init_successfully);
    RUN_TEST(test_should_create_window);
    RUN_TEST(test_should_fail_to_create_window);
    RUN_TEST(test_should_setup_windows_unsuccessfully);
    RUN_TEST(test_should_setup_windows_successfully);
    RUN_TEST(test_should_close_window_succesffully);
    RUN_TEST(test_should_fail_vertex_shader);
    RUN_TEST(test_should_create_vertex_shader);
    RUN_TEST(test_should_fail_fragment_shader);
    RUN_TEST(test_should_fail_shader_linking);
    RUN_TEST(test_should_link_shaders);
    RUN_TEST(test_should_fail_link_vertex_attributes);
    RUN_TEST(test_should_link_vertex_attributes);
    RUN_TEST(test_should_draw_triangle);
    RUN_TEST(test_should_draw_square);
    return UNITY_END();
}