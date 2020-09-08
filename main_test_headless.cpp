#include "Unity/src/unity.h"
#include <iostream>
#include <sstream>
#include "opengl_ults.h"
#include "string.h"
#include "unistd.h"


std::stringstream buffer1;
std::streambuf * old1;


/*
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


void test_should_close_window_succesffully(void) {

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
    bool result = myclass.createFragmentShader();
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    //TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\n");  
    //TEST_ASSERT_FALSE(result);
    TEST_IGNORE_MESSAGE("To cause test to fail mess up syntax of fragment src or pass frag shader incorrect shader type");
}

void test_should_create_fragment_shader(void)
{
    Opengl_ults myclass;
    const char* array;
    int result;

    setupOpenGLUtls(&myclass);
    result = myclass.createFragmentShader();
    array = cleanup();

    TEST_ASSERT_EQUAL_STRING(array, "");  
    TEST_ASSERT_NOT_EQUAL(result,0);
}

void test_should_fail_shader_linking(void)
{
    Opengl_ults myclass;
    const char* array;

    setupOpenGLUtls(&myclass);
    int vertexShader = myclass.createFragmentShader();
    int shaderProgram = myclass.linkShaders(vertexShader, -1);
    array = cleanup();

    //TEST_ASSERT_EQUAL_STRING(array, "Failed to create GLFW window\nFailed to create GLFW window\n");  
    //TEST_ASSERT_EQUAL(shaderProgram, 0);
    TEST_IGNORE_MESSAGE("To cause test to pass remove line 'out vec4 FragColor;\n' in frag source");
}

void test_should_link_shaders(void)
{
    Opengl_ults myclass;
    myclass.init();

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader();
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
    float vertices [] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f, 0.5f, 0.0f, 
    };
    Opengl_ults myclass;
    myclass.init();

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  

    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader();
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    bool result = myclass.linkingAttributes(vertices, sizeof(vertices));
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
      float vertices [] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f, 0.5f, 0.0f, 
    };
    Opengl_ults myclass;
    myclass.init();
    myclass.setupWindows(3,3);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    
    int vertexShader = myclass.createFragmentShader();
    int fragmentShader = myclass.createFragmentShader();
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    bool result = myclass.linkingAttributes(vertices, sizeof(vertices));
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);

    TEST_ASSERT_EQUAL_STRING(array, "");  
    //TEST_ASSERT_TRUE(result);
}

void test_should_link_element()
{
   float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
     int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    Opengl_ults myclass;
    myclass.init();

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  
    int vertexShader = myclass.createVertexShader();
    int fragmentShader = myclass.createFragmentShader();
    int programShader = myclass.linkShaders(vertexShader, fragmentShader);
    int vao = myclass.linkingAttributes(vertices, sizeof(vertices));
    int ebo = myclass.linkElementBuffer(indices, sizeof(indices));
    
    std::string text = buffer.str(); 
    const char *array = text.c_str();

    // Reset buffer
    std::cout.rdbuf(old);
    printf("%d", ebo);
    TEST_ASSERT_EQUAL_STRING(array, "");  
}


// not needed when using generate_test_runner.rb
int main(void) 
{
    UNITY_BEGIN();

    RUN_TEST(test_should_fail_vertex_shader);
    RUN_TEST(test_should_create_vertex_shader);
    RUN_TEST(test_should_fail_fragment_shader);
    RUN_TEST(test_should_fail_shader_linking);
    RUN_TEST(test_should_link_shaders);
    RUN_TEST(test_should_fail_link_vertex_attributes);
    RUN_TEST(test_should_link_vertex_attributes);
    RUN_TEST(test_should_link_element);
    return UNITY_END();
}
*/