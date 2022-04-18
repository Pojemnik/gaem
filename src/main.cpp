#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

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
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void errorCallback(int error, const char* description)
{
    std::cerr << description << std::endl;
}

void draw(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 1.5f, -1.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.01f, 50.0f);
    exampleLambert->setUniformMatrix("P", P);
    exampleLambert->setUniformMatrix("V", V);
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
