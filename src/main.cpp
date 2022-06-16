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
#include "transform.h"
#include "rigidbody.h"

const float MAX_PLAYER_SPEED = 5.F;
const float PLAYER_ACCELERATION = 30.F;
const float GRAVITY = 12.F;
const float PLAYER_FRICTION = 20.F;
const float PLAYER_JUMP_FORCE = 12.F;

std::unique_ptr<Shader> simple;
std::unique_ptr<Shader> textShader;
std::unique_ptr<Shader> skyboxShader;
std::unique_ptr<Shader> flat;
std::unique_ptr<Camera> camera;
std::unique_ptr<Text> fpsCounter;
std::unique_ptr<Text> scoreCounter;
std::unique_ptr<Skybox> skybox;
std::vector<Transform> staticObjects;
std::vector<Collider*> colliders;
std::unique_ptr<Rigidbody> playerRB;
std::unique_ptr<Transform> playerTransform;
std::vector<Transform> stars;

int score = 0;

void freeResources()
{

}

void initResources()
{
	simple = std::make_unique<Shader>("src/shaders/f_simple.glsl", "src/shaders/v_simple.glsl");
	textShader = std::make_unique<Shader>("src/shaders/f_text.glsl", "src/shaders/v_text.glsl");
	skyboxShader = std::make_unique<Shader>("src/shaders/f_skybox.glsl", "src/shaders/v_skybox.glsl");
	flat = std::make_unique<Shader>("src/shaders/f_flat.glsl", "src/shaders/v_flat.glsl");
	glEnable(GL_DEPTH_TEST);
	std::vector<int> trackedKeys{ GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A,
		GLFW_KEY_D, GLFW_KEY_ESCAPE, GLFW_KEY_SPACE };
	Keyboard::addTrackedKeys(trackedKeys);
	Resources::addVertexArray("block_2x2_2", "assets/models/stone_block_2x2_2.obj");
	Resources::addVertexArray("star", "assets/models/star.obj");
	Resources::addTexture("rock", "assets/textures/rock.png");
	playerRB = std::make_unique<Rigidbody>(GRAVITY, PLAYER_FRICTION, MAX_PLAYER_SPEED);
	playerTransform = std::make_unique<Transform>(vec3(0, 0, 0));
	float offset = 5;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			vec3 pos = vec3(i * offset, -2, j * offset);
			staticObjects.emplace_back(pos);
			staticObjects.back().createDrawableObject(Resources::getVertexArray("block_2x2_2"));
			staticObjects.back().getDrawableObject()->addTexture(std::make_shared<Texture>(Resources::getTexture("rock")));
			staticObjects.back().createCollider(vec3(2, 1, 2), pos);
			colliders.push_back(&*staticObjects.back().getCollider());
		}
	}

	stars.emplace_back(vec3(5, 1, 3));
	stars.back().createDrawableObject(Resources::getVertexArray("star"));
	stars.back().getDrawableObject()->scale(vec3(0.15f));

	fpsCounter = std::make_unique<Text>();
	scoreCounter = std::make_unique<Text>();
	std::vector<std::string> skyboxFilenames =
	{
		"assets/textures/skybox/humble_rt.png",
		"assets/textures/skybox/humble_lf.png",
		"assets/textures/skybox/humble_up.png",
		"assets/textures/skybox/humble_dn.png",
		"assets/textures/skybox/humble_bk.png",
		"assets/textures/skybox/humble_ft.png"
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

	if (Keyboard::isKeyPressed(GLFW_KEY_SPACE))
	{
		if (playerRB->isColliding())
		{
			playerRB->addVelocity(glm::vec3(0, 1, 0) * PLAYER_JUMP_FORCE);
		}
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_W))
	{
		playerRB->addVelocity(camera->getDirectionOnPlane() * timeDelta * 1.f * PLAYER_ACCELERATION);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_S))
	{
		playerRB->addVelocity(camera->getDirectionOnPlane() * timeDelta * -1.f * PLAYER_ACCELERATION);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_A))
	{
		vec3 forward = camera->getDirectionOnPlane();
		vec3 right = glm::cross(forward, vec3(0, 1, 0));
		playerRB->addVelocity(right * timeDelta * -1.f * PLAYER_ACCELERATION);
	}
	if (Keyboard::isKeyPressed(GLFW_KEY_D))
	{
		vec3 forward = camera->getDirectionOnPlane();
		vec3 right = glm::cross(forward, vec3(0, 1, 0));
		playerRB->addVelocity(right * timeDelta * 1.f * PLAYER_ACCELERATION);
	}
	Mouse::updateMousePosition(window);
	vec2 cursorDelta = Mouse::getCursorDelta() * 0.02f;
	vec2 cameraInput = InputAdapter::mouseDeltaToCameraInput(cursorDelta);
	playerRB->update(timeDelta, colliders, *playerTransform);
	vec3 cameraPos = playerTransform->getPosition() + vec3(0, 1, 0);
	camera->moveTo(cameraPos);
	camera->set2DRotation(cameraInput);
	camera->update();

	fpsCounter->setText(std::to_string(static_cast<int>(round(1.f / timeDelta))));

	for (auto& it : staticObjects)
	{
		it.getDrawable()->draw(*camera, *flat);
	}

	std::vector<int> toRemove;
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].moveRelative(vec3(0.5f, 0, 2));
		stars[i].rotateDeg(60.f * timeDelta, vec3(0, 1, 0));
		stars[i].moveRelative(vec3(-0.5f, 0, -2));
		stars[i].getDrawable()->draw(*camera, *simple, vec4(1,1,0,1));
		float distance = glm::length(stars[i].getPosition() - cameraPos);
		if (distance < 0.5f)
		{
			toRemove.push_back(i);
			score++;
			scoreCounter->setText("Score: " + std::to_string(score));
		}
	}

	for (const auto& it : toRemove)
	{
		stars.erase(stars.begin() + it);
	}

	skybox->draw(*camera, *skyboxShader);

	fpsCounter->draw(*camera, *textShader);
	scoreCounter->draw(*camera, *textShader);

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
	camera = std::make_unique<Camera>(vec3(0.f, 0.f, 0.f), glm::radians(50.f), 1.0f, 0.01f, 500.0f, window);
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

	fpsCounter->setPosition(vec2(0.f, 880.f));
	fpsCounter->setScale(0.5f);

	scoreCounter->setPosition(vec2(1100.f, 880.f));
	scoreCounter->setScale(0.5f);
	scoreCounter->setText("Score: " + std::to_string(score));

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