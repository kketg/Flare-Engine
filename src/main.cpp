#include <iostream>
//******always include glad before glfw********
#include <../include/glad/glad.h>
#include <../include/glfw/glfw3.h>
using namespace std;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};
//temp containers for shaders
const char *vertexShaderCode = "#version 330 core\n"
                               "//declares input attributes (in this case, the vertex attribute position)\n"
                               "//Sets location of input variable\n"
                               "layout(location = 0) in vec3 aPos;\n"
                               "void main()\n"
                               "{\n"
                               "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                               "}\0";
const char *fragmentShaderCode = "#version 330 core\n"
                                 "//variable to be output\n"
                                 "out vec4 FragColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "}\0";

void fail(string error)
{

    std::cout << "Error: " << error;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    //Closes window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else
    {
        //gets the name of the key
        std::cout << glfwGetKeyName(key, scancode);
    }
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{

    int windowWidth = 1280;
    int windowHeight = 720;

    //Creates a window pointer
    GLFWwindow *window;

    //initializes GLFW
    if (!glfwInit())
    {
        fail("GLFW failed to initialize");
        return -1;
    }

    //Configures glfw       docs:https://www.glfw.org/docs/latest/window.html#window_hints
    //Sets compatability
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Specifies the opengl profile to create the context for (core, compat, any)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Initializes window
    window = glfwCreateWindow(windowWidth, windowHeight, "Flare", NULL, NULL);

    if (!window)
    {
        fail("Window failed to initialize");
        return -1;
    }

    //called whenever a key is pressed, repeated, or released  (key_callback is declared above)
    //handles input
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    //Initializes GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fail("GLAD failed to initialize");
        return -1;
    }

    glfwSwapInterval(1);

    //Creates an opengl viewport in which we can render tingz!
    glViewport(0, 0, windowWidth, windowHeight);

    //called whenever the window is resized so that opengl can resize the viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //**********************************************************************VAO**********************************************************************

    //Creates VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //***********************************************************************************************************************************************

    //**********************************************************************VBO**********************************************************************
    //Creates a Vertex Buffer Object. This allows us to send a large amount of vertex data directly to the GPU memory.
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //Binds buffer to buffer type target(only one buffer can be assigned to each type at a time)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Allocates memory and stores data within initialized memory in the buffer
    //Specifically designed to copy user-defined data into buffer (in this case, the vertices array)
    //Specifies how the GPU will handle the data (GL_STREAM_DRAW, GL_STATIC_DRAW, GL_DYNAMIC_DRAW)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //***********************************************************************************************************************************************

    //**********************************************************************VERTEX ATTRIBUTES**********************************************************************
    //Vertex layout to configure (SPECIFIED IN VERTEX SHADER)
    //Size of vertex attribute (vector3)
    //Type of data
    //Normalize data?
    //stride(space between consecutive vertex attributes)
    //offset of where position data begins in buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //Enables vertex attributes
    glEnableVertexAttribArray(0);

    //***********************************************************************************************************************************************

    //***********************************************************************SHADERS***********************************************************************
    //Creates shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Compiles the shader
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    //Gets compilation outcome
    int vSuccess;
    char vInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);
    if (!vSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vInfoLog);
        fail("Vertex shader failed to compile: " + (string)vInfoLog);
        return -1;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    int fSuccess;
    char fInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);
    if (!fSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fInfoLog);
        fail("Fragment shader failed to compile: " + (string)fInfoLog);
        return -1;
    }

    //Creates shader program (final linked version of all the shaders)
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //Attaches all the shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //Links shader program to opengl
    glLinkProgram(shaderProgram);
    int pSuccess;
    char pInfoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &pSuccess);
    if (!pSuccess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, pInfoLog);
        fail("Shader program failed to initialize: " + (string)pInfoLog);
    }

    //We are deleting the shaders, as they have been linked into the shader program, and are no longer needed.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //*****************************************************************************************************************************************************

    while (!glfwWindowShouldClose(window))
    {

        //********************************Rendering********************************
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //Clears rendering buffers (When only rendering color to the screen, it only clears the color buffer)
        glClear(GL_COLOR_BUFFER_BIT);

        //Assigned shader program to opengl
        glUseProgram(shaderProgram);
        //Binds VAOs
        glBindVertexArray(VAO);
        //Draws primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //*************************************************************************

        //Checks if any events are triggered, updates the window state, and calls callback functions
        glfwPollEvents();
        //swap color buffer used to render window
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}