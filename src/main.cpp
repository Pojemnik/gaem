#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <numeric>

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
#include "window.h"
#include "resources.h"
#include "skybox.h"

std::unique_ptr<Shader> simple;
std::unique_ptr<Shader> textShader;
std::unique_ptr<Shader> skyboxShader;
std::unique_ptr<Shader> light;
std::unique_ptr<DrawableObject> chemirailObject;
std::unique_ptr<DrawableObject> chemirailObject2;
std::unique_ptr<Camera> camera;
std::unique_ptr<Text> text;
std::unique_ptr<Skybox> skybox;
std::vector<DrawableObject> staticObjects;

void freeResources()
{

}

void initResources()
{
	simple = std::make_unique<Shader>("src/shaders/f_simple.glsl", "src/shaders/v_simple.glsl");
	textShader = std::make_unique<Shader>("src/shaders/f_text.glsl", "src/shaders/v_text.glsl");
	skyboxShader = std::make_unique<Shader>("src/shaders/f_skybox.glsl", "src/shaders/v_skybox.glsl");
	light = std::make_unique<Shader>("src/shaders/f_flat.glsl", "src/shaders/v_flat.glsl");
	glEnable(GL_DEPTH_TEST);
	std::vector<int> trackedKeys{ GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A,
		GLFW_KEY_D, GLFW_KEY_ESCAPE };
	Keyboard::addTrackedKeys(trackedKeys);
	Resources::addVertexArray("chemirail", "assets/models/untitled.obj");
	Resources::addVertexArray("block_2x2_2", "assets/models/stone_block_2x2_2.obj");
	Resources::addTexture("rock", "assets/textures/rock.png");
	chemirailObject = std::make_unique<DrawableObject>(Resources::getVertexArray("chemirail"));
	chemirailObject2 = std::make_unique<DrawableObject>(Resources::getVertexArray("chemirail"));
	staticObjects.emplace_back(Resources::getVertexArray("block_2x2_2"));
	staticObjects.back().move(vec3(0, -2, 0));
	staticObjects.back().addTexture(std::make_shared<Texture>(Resources::getTexture("rock")));
	chemirailObject->addTexture(std::make_shared<Texture>(Resources::getTexture("rock")));
	chemirailObject2->move(vec3(2, 0, 0));
	chemirailObject->move(vec3(0, 2, 0));
	text = std::make_unique<Text>();
	std::vector<std::string> skyboxFilenames =
	{
		"assets/textures/skybox/humble_rt.png",
		"assets/textures/skybox/humble_lf.png",
		"assets/textures/skybox/humble_up.png",
		"assets/textures/skybox/humble_dn.png",
		"assets/textures/skybox/humble_ft.png",
		"assets/textures/skybox/humble_bk.png"
	};
	skybox = std::make_unique<Skybox>(skyboxFilenames);
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

	if (Keyboard::isKeyPressed(GLFW_KEY_W))
	{
		camera->move(glm::vec3(0, 0, 1) * timeDelta);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_S))
	{
		camera->move(glm::vec3(0, 0, -1) * timeDelta);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_A))
	{
		camera->move(glm::vec3(-1, 0, 0) * timeDelta);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_D))
	{
		camera->move(glm::vec3(1, 0, 0) * timeDelta);
	}
	Mouse::updateMousePosition(window);
	vec2 cursorDelta = Mouse::getCursorDelta() * timeDelta;
	vec2 cameraInput = InputAdapter::mouseDeltaToCameraInput(cursorDelta);
	camera->set2DRotation(cameraInput);
	camera->update();

	text->setText(std::to_string(static_cast<int>(round(1.f / timeDelta))));

	chemirailObject->rotate(timeDelta, vec3(0, 1, 0));
	chemirailObject->draw(*camera, *simple);
	chemirailObject2->rotate(-timeDelta, vec3(0, 1, 0));
	chemirailObject2->draw(*camera, *light);
	for (auto& it : staticObjects)
	{
		it.draw(*camera, *light);
	}

	skybox->draw(*camera, *skyboxShader);

	text->draw(*camera, *textShader);

	glfwSwapBuffers(window);
}

int main(void)
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization error" << std::endl;
		return 1;
	}

	Window window(glm::vec2(1200, 900), "Gaem");
	camera = std::make_unique<Camera>(vec3(0.f, 0.f, 0.f), glm::radians(50.f), 1.0f, 0.01f, 50.0f, window);
	GLenum glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK)
	{
		std::cerr << "GLEW initialization error: " << glewInitResult << std::endl;
		return 1;
	}
	initResources();

	
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window.getWindow(), Keyboard::keyCallback);
	glfwSetCursorPosCallback(window.getWindow(), Mouse::cursorPositionCallback);
	glfwSetMouseButtonCallback(window.getWindow(), Mouse::mouseButtonCallback);
	Keyboard::addKeyPressedListener(GLFW_KEY_ESCAPE, "ESCAPE_CURSOR_CALLBACK", std::bind(Mouse::unlockCursor, window.getWindow()));
	Mouse::lockCursor(window.getWindow());

	text->setPosition(vec2(0.f, 880.f));
	text->setScale(0.5f);

	glfwSetTime(0);
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		float time = glfwGetTime();
		glfwSetTime(0);
		draw(window.getWindow(), time);
		glfwPollEvents();
		printOpenGLErrorIfAny();
	}

	Keyboard::removeKeyPressedListener(GLFW_KEY_ESCAPE, "ESCAPE_CURSOR_CALLBACK");
	freeResources();
	glfwTerminate();
	return 0;
}