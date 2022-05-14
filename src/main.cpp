#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <functional>

#include "main.h"
#include "definitions.h"
#include "shader.h"
#include "model.h"
#include "drawableObject.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "inputAdapter.h"
#include "util.h"
#include "text.h"

std::unique_ptr<Shader> exampleLambert;
std::unique_ptr<Shader> exampleConstant;
std::unique_ptr<Shader> simple;
std::unique_ptr<Shader> textShader;
std::unique_ptr<DrawableObject> chemirailObject;
std::unique_ptr<DrawableObject> chemirailObject2;
std::unique_ptr<Camera> camera;
std::unique_ptr<Text> text;

void freeResources()
{

}

void initResources()
{
	exampleLambert = std::make_unique<Shader>("src/shaders/example/f_lambert.glsl", "src/shaders/example/v_lambert.glsl");
	exampleConstant = std::make_unique<Shader>("src/shaders/example/f_constant.glsl", "src/shaders/example/v_constant.glsl");
	simple = std::make_unique<Shader>("src/shaders/f_simple.glsl", "src/shaders/v_simple.glsl");
	textShader = std::make_unique<Shader>("src/shaders/f_text.glsl", "src/shaders/v_text.glsl");
	textShader->use();
	glEnable(GL_DEPTH_TEST);
	std::vector<int> trackedKeys{ GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A,
		GLFW_KEY_D, GLFW_KEY_ESCAPE };
	Keyboard::addTrackedKeys(trackedKeys);
	chemirailObject = std::make_unique<DrawableObject>("assets/models/untitled.obj");
	chemirailObject2 = std::make_unique<DrawableObject>("assets/models/untitled.obj");
	chemirailObject2->move(vec3(2, 0, 0));
	camera = std::make_unique<Camera>(vec3(0.f, 0.f, 2.f), glm::radians(50.f), 1.0f, 0.01f, 50.0f);
	text = std::make_unique<Text>();
}

void errorCallback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void draw(GLFWwindow* window, float timeDelta)
{
	static float timeAcc(0);
	timeAcc += timeDelta;
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//if (Keyboard::isKeyPressed(GLFW_KEY_W))
	//{
	//	camera->move(glm::vec3(0, 0, 1) * timeDelta);
	//}
	//if (Keyboard::isKeyPressed(GLFW_KEY_S))
	//{
	//	camera->move(glm::vec3(0, 0, -1) * timeDelta);
	//}
	//if (Keyboard::isKeyPressed(GLFW_KEY_A))
	//{
	//	camera->move(glm::vec3(-1, 0, 0) * timeDelta);
	//}
	//if (Keyboard::isKeyPressed(GLFW_KEY_D))
	//{
	//	camera->move(glm::vec3(1, 0, 0) * timeDelta);
	//}
	//Mouse::updateMousePosition(window);
	//vec2 cursorDelta = Mouse::getCursorDelta() * timeDelta;
	//vec2 cameraInput = InputAdapter::mouseDeltaToCameraInput(cursorDelta);
	//camera->set2DRotation(cameraInput);
	//camera->update(*simple.get());

	//chemirailObject->rotate(timeDelta, vec3(0, 1, 0));
	//chemirailObject->draw(*simple);
	//chemirailObject2->rotate(-timeDelta, vec3(0, 1, 0));
	//chemirailObject2->draw(*simple);

	text->draw(*textShader);

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

	glViewport(0.f, 0.f, 640.f, 480.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window, Keyboard::keyCallback);
	glfwSetCursorPosCallback(window, Mouse::cursorPositionCallback);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	Keyboard::addKeyPressedListener(GLFW_KEY_ESCAPE, "ESCAPE_CURSOR_CALLBACK", std::bind(Mouse::unlockCursor, window));
	Mouse::lockCursor(window);
	text->init(*textShader);
	text->setText("test");
	text->setPosition(vec2(0.f, 0.f));
	glfwSetTime(0);
	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		glfwSetTime(0);
		draw(window, time);
		glfwPollEvents();
		printOpenGLErrorIfAny();
	}

	Keyboard::removeKeyPressedListener(GLFW_KEY_ESCAPE, "ESCAPE_CURSOR_CALLBACK");
	freeResources();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
