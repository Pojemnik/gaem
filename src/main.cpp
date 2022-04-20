#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

#include <iostream>
#include <memory>

#include "main.h"
#include "definitions.h"
#include "shader.h"
#include "model.h"
#include "objectRenderer.h"
#include "camera.h"

std::unique_ptr<Shader> exampleLambert;
std::unique_ptr<Shader> exampleConstant;
ObjectRenderer chemirailObject = ObjectRenderer(std::move(std::make_unique<Model>("assets/models/untitled.obj")));
Camera camera = Camera(vec3(0.f,0.f,-2.f), vec3(0.f,0.f,0.f), glm::radians(50.f), 1.0f, 0.01f, 50.0f);

void freeResources()
{

}

void initResources()
{
	exampleLambert = std::make_unique<Shader>("src/shaders/example/f_lambert.glsl", "src/shaders/example/v_lambert.glsl");
	exampleConstant = std::make_unique<Shader>("src/shaders/example/f_constant.glsl", "src/shaders/example/v_constant.glsl");
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
}

void errorCallback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void draw(GLFWwindow* window, float timeDelta)
{
	static float timeAcc(0);
	timeAcc += timeDelta;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	exampleConstant->use();
	camera.update(*exampleConstant.get());

	chemirailObject.rotate(timeDelta, vec3(0, 1, 0));
	chemirailObject.draw(*exampleConstant.get());

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
	if (glewInitResult != GLEW_OK)
	{
		std::cerr << "GLEW initialization error: " << glewInitResult << std::endl;
		return 1;
	}
	initResources();

	glfwSetTime(0);
	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		glfwSetTime(0);
		draw(window, time);
		glfwPollEvents();
	}

	freeResources();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
