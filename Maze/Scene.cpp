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

#define Multithreading true //multithreading not working because
typedef std::vector<std::vector<std::vector<std::shared_ptr<GameObject>>>> yzxGameObject;

Scene::Scene()
{
	_lastFrameTime = glfwGetTime();
	_camera = std::make_shared<ThirdPersonCamera>();
	_loadScreen = std::make_shared<LoadScreen>(new Texture("resources\\modelsv1\\wall\\Rock037_4K_Color.jpg"));

	loadLevel("resources/levels/firstData.txt");
}

void Scene::draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//check if window has resized
	if (viewport[2] != width || viewport[3] != height)
	{
		glViewport(0, 0, width, height);
	}
	if (_state != RUNNING) {
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
static bool bener = false;

void Scene::update()
{
	//calculate time passed since last frame
	double currentFrameTime = glfwGetTime();
	float deltaTime = (float)(currentFrameTime - Scene::_lastFrameTime);
	_lastFrameTime = currentFrameTime;

	if (_state == STATE::ReloadPending) {
		//reset scene
		reset();
#if Multithreading
		startLoading();
		_thread = std::thread(LoadNewSceneAsync, this, _localPathCopy);
#else
		LoadNewScene(*this, _localPathCopy);
		stopLoading();
#endif
	}
	else if (_state == STATE::READY) {
		_player = (_buffer[0]);
		_camera->setSubject(_player.get());

		//add gameObjects to scene
		for (auto& gameObject : _buffer) {
			addGameObject(gameObject);
		}
		_buffer.clear();
		_state = STATE::RUNNING;
	}

	if (_state != RUNNING)
	{
		_loadScreen->update(deltaTime);
	}
	else {
		//update logic
		int count = 0;
		if (!bener) {
			bener = true;
			for (std::shared_ptr<GameObject> gameObject : Scene::_gameObjects) {
				count++;
				std::cout << count << std::endl;
				gameObject->update(deltaTime);
			}
			_player->update(deltaTime);
			_camera->update(deltaTime);
			bener = false;
		}
		else {
			std::cout << "failed";
		}
	}
	this->draw();
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	this->_gameObjects.push_back(gameObject);
}

void Scene::addGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
	this->_buffer = gameObjects;
}

void Scene::reset() {
	_gameObjects.clear();
	_player = nullptr;
	_camera->setSubject(_player.get());
}

void Scene::loadLevel(const std::string& path)
{
	//create copy for live reload
	_localPathCopy = path.c_str();
	_state = STATE::ReloadPending;
}

void Scene::startLoading() {
	_state = STATE::LOADING;
}
void Scene::stopLoading() {
	_state = STATE::READY;
}
