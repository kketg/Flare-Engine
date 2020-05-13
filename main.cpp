#include <cstdio>

#include <GLFW/glfw3.h>

void fail() {

    printf("Something went wrong.");

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

}

int main() {

    GLFWwindow* window;

    if (!glfwInit()) {
        fail();
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Example", NULL, NULL);

    if (!window) {
        fail();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {

        glfwSwapBuffers(window);
        glfwPollEvents();
        printf("");

    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}