#include "Scene.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"
#include "tigl.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "ObjectLoader.hpp"
#include "imgui.h"
#include "utills.hpp"
#include "Button.hpp"
#include "Sun.hpp"
#include "MovingWall.hpp"
#include "AbstractLevelDataReader.hpp"
#include "LevelLoader.hpp"
#include <iostream>
#include "glfwManager.hpp"
#include "Texture.hpp"
#include "LoadScene.hpp"
#include <future>

#define Multithreading true 


typedef std::vector<std::vector<std::vector<std::shared_ptr<GameObject>>>> yzxGameObject;

Scene::Scene()
{
	_sunLight = lightInfo();
	_sunLight.isDirectional = true;
	_sunLight.specular = glm::vec3(1);

	_sunLight.position = glm::normalize(glm::vec3(1));
	_sunLight.diffusion = glm::vec3(0.5f);
	_sunLight.ambient = glm::vec3(0.5f);

	_lastFrameTime = glfwGetTime();
	_camera = std::make_shared<ThirdPersonCamera>();

	auto loadTextures = std::vector<Texture*>{
		new Texture("resources\\loadingScreen\\loadingscreenv1.png"),
		new Texture("resources\\mazes\\Maze2.png")
	};

	_loadScreen = std::make_shared<LoadScreen>(loadTextures);
	loadLevel("resources/levels/firstData.txt");
}

void Scene::draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int width, height;
	glfwGetWindowSize(Window, &width, &height);
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//check if window has resized
	if (viewport[2] != width || viewport[3] != height)
	{
		glViewport(0, 0, width, height);
	}
	if (state != RUNNING) {
		_loadScreen->draw();
	}
	else {
		glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

		glEnable(GL_DEPTH_TEST);

		tigl::shader->setProjectionMatrix(projection);
		tigl::shader->setModelMatrix(glm::mat4(1.0f));

		for (auto& gameObject : _gameObjects) {
			gameObject->draw();
		}
	}
}

void Scene::update()
{
	//calculate time passed since last frame
	double currentFrameTime = glfwGetTime();
	float deltaTime = (float)(currentFrameTime - Scene::_lastFrameTime);
	_lastFrameTime = currentFrameTime;

	if (state == ReloadPending) {
		//reset scene
		reset();
#if Multithreading
		//startLoading();
		addLight(&_sunLight);
		_thread = std::thread(LoadNewSceneAsync, this, _currentLevelPath);
#else
		LoadNewScene(*this, _currentLevelPath);
		_state = RUNNING;
#endif
	}
#if Multithreading
	else if (state == READY) {
		_thread.join();//gracefully stop thread so it can be reused
		state = RUNNING;
		removeLight(&_sunLight);

	}
#endif

	if (state != RUNNING)
	{
		_loadScreen->update(deltaTime);
	}
	else {
		//update logic
		for (std::shared_ptr<GameObject> gameObject : Scene::_gameObjects) {
			gameObject->update(deltaTime);
		}
		_player->update(deltaTime);
		_camera->update(deltaTime);
	}
	this->draw();
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	this->_gameObjects.push_back(gameObject);
}

void Scene::addGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
	_player = (gameObjects[0]);
	_camera->setSubject(_player.get());

	//add gameObjects to scene
	for (auto& gameObject : gameObjects) {
		addGameObject(gameObject);
	}
}

void Scene::reset() {
	_gameObjects.clear();
	_player = nullptr;
	_camera->setSubject(nullptr);
}

void Scene::loadLevel(const std::string& path)
{
	//create copy for live reload
	_currentLevelPath = path.c_str();
	state = ReloadPending;
}
