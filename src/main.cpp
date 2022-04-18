#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>
#include <memory>

#include "main.h"
#include "shader.h"

std::unique_ptr<Shader> exampleLambert;

void freeResources()
{

}

void initResources()
{
    exampleLambert = std::make_unique<Shader>("src/shaders/example/f_lambert.glsl", "src/shaders/example/v_lambert.glsl");
}

void errorCallback(int error, const char* description)
{
    std::cerr << description << std::endl;
}

void draw(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization error" << std::endl;
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Gaem", NULL, NULL);
    if (!window)
    {
        std::cerr << "Window creation error" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    GLenum glewInitResult = glewInit();
    if(glewInitResult != GLEW_OK)
    {
        std::cerr << "GLEW initialization error: "  << glewInitResult << std::endl;
        return 1;
    }
    initResources();

    while (!glfwWindowShouldClose(window))
    {
        float time = glfwGetTime();
        glfwSetTime(0);
        draw(window);
        glfwPollEvents();
    }

    freeResources();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
