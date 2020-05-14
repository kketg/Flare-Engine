#include <iostream>
//******always include glad before glfw********
#include <../include/glad/glad.h>
#include <../include/glfw/glfw3.h>
using namespace std;

void fail(string error) {

    std::cout << "Error: " << error;

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //Closes window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else
    {
                    //gets the name of the key
        std::cout << glfwGetKeyName(key,scancode);
    }
    

}

int main() {

    //Creates a window pointer
    GLFWwindow* window;

    //initializes GLFW
    if (!glfwInit()) {
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
    window = glfwCreateWindow(1280, 720, "Flare", NULL, NULL);

    if (!window) {
        fail("Window failed to initialize");
        return -1;
    }

    //called whenever a key is pressed, repeated, or released  (key_callback is declared above)
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window)) {

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}