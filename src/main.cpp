#include <GLFW/glfw3.h>
//#include <GL/GL.h>
#include <iostream>
using namespace std;


int main()
{
    
    if(!glfwInit())
    {
        return -1;
    }
                            //width, height, name, monitor info, context sharing
    GLFWwindow* gameWindow = glfwCreateWindow(1280, 720, "Flare", NULL, NULL);
    if(!gameWindow)
    {
        glfwTerminate();
        return -1;
    }
    //Creates an opengl context in the game window
    glfwMakeContextCurrent(gameWindow);

    // Application (Game) loop
    while(!glfwWindowShouldClose(gameWindow))
    {
        double time = glfwGetTime();
        int width, height;
        glfwGetFramebufferSize(gameWindow, &width, &height);
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(gameWindow);
        glfwPollEvents();
    }

    glfwTerminate();    
    return 0;
}