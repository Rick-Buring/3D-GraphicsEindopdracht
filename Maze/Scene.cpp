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

void Scene::draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	glEnable(GL_DEPTH_TEST);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	for (auto gameObject : _gameObjects) {
		gameObject->draw();
	}
	_player->draw();
}

Scene::Scene()
{
	_camera = std::make_shared<ThirdPersonCamera>();
	loadLevel("resources/levels/firstData.txt");
}

void Scene::update()
{
	//calculate time passed since last frame
	double currentFrameTime = glfwGetTime();
	double deltaTime = currentFrameTime - Scene::_lastFrameTime;
	_lastFrameTime = currentFrameTime;

	//update logic

	for (auto gameObject : Scene::_gameObjects) {
		gameObject->update((float)deltaTime);
	}
	_player->update(deltaTime);
	_camera->update(deltaTime);

	this->draw();
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	this->_gameObjects.push_back(gameObject);
}

std::shared_ptr<std::vector<Model3D_t>> findModel(const std::string& name, std::vector<NamedModel3D_t>& list) {
	for (auto obj : list) {
		if (obj.modelName == name) {
			return obj.model;
		}
	}
	return nullptr;
}

void Scene::reset() {
	_gameObjects.clear();
	_player = nullptr;
	_camera->setSubject(_player.get());
}

void Scene::loadLevel(const std::string& path)
{
	char localPathCopy[50];
	strncpy_s(localPathCopy, path.c_str(), path.size());
	reset();

	std::shared_ptr<std::vector<Model3D_t>> cube = buildCube(glm::vec3(0), glm::vec3(0.5), glm::vec4(2));
	std::shared_ptr<std::vector<Model3D_t>> sphere = buildSphere(glm::vec3(0), glm::vec3(0.5), glm::vec4(2));

	//load file with factory patern 
	std::string filePath = localPathCopy;
	AbstractLevelDataReader* reader = getReader(filePath);
	std::vector<LevelData_t> levelData = reader->readData(filePath);

	//load 3d models
	auto models = loadObjects(levelData[0].path);

	//load maze image
	std::string mazePath = levelData[1].path;
	loadMazeFromFile(mazePath, cube);

	for (size_t i = 2; i < levelData.size(); i++)
	{
		levelData_st data = levelData[i].data;
		std::string dataType = data.type;

		if (dataType == "player") {
			//only one player per level
			if (_player)
				continue;

			_player = std::make_shared<Player>(findModel("player", models));
			_player->scale = glm::vec3(0.2f);
			_player->position = data.position;

			_camera->setSubject(_player.get());
		}
		else if (dataType == "sun")
		{
			//create sun
			auto sun = std::make_shared<Sun>(sphere);
			sun->scale = glm::vec3(5.0f);
			addGameObject(sun);
		}
		else if (dataType == "butten") {
			//std::shared_ptr<std::vector<Model3D_t>> model, GameObject* player, glm::vec3 position, InteractableGameObject* interactableObj = nullptr)
			std::shared_ptr<InteractableGameObject> interactingObject = nullptr;

			if (std::string(data.linkedWithType) == "moving_wall") {
				interactingObject = std::make_shared<MovingWall>(cube, data.Linkedposition, data.action);
			}

			if (interactingObject)
				addGameObject(interactingObject);

			auto butten = std::make_shared<Button>(cube, _player.get(), data.position, interactingObject.get());
			butten->scale = glm::vec3(.5f);
			addGameObject(butten);
		}
		else if (dataType == "level") {
  			std::shared_ptr<LevelLoader> levelLoader = LevelLoader::createLevelLoader(data.linkedWithType, this);
			if (levelLoader) {
				addGameObject(levelLoader);

				auto butten = std::make_shared<Button>(cube, _player.get(), data.position, levelLoader.get());
				butten->scale = glm::vec3(.5f);
				addGameObject(butten);
			}
		}

	}




}

void Scene::loadMazeFromFile(std::string mazePath, std::shared_ptr<std::vector<Model3D_t>>& cube)
{
	int width, height, bpp;
	unsigned char* image = stbi_load(mazePath.c_str(), &width, &height, &bpp, 4);

	for (size_t z = 0; z < height; z++)
	{
		for (size_t x = 0; x < width * 4; x += 4)
		{
			//objects position is x y z
			//x is encoded in width of image
			//z is encoded in height of image
			//y is encoded in color channel of image
			//value in chanel is the index of the object to render
			int r = image[z * height * 4 + x + 0];
			int g = image[z * height * 4 + x + 1];
			int b = image[z * height * 4 + x + 2];

			//alpha not usefull image cant create image with r,b,g value x and alpha 0
			int a = image[z * height * 4 + x + 3];

			//todo create 3d objects based off decoded values
			if (r) {
				std::shared_ptr<GameObject> c = std::make_shared<GameObject>(cube);
				c->position.x = (x / 4);
				c->position.z = z;
				c->position.y = 0;
				addGameObject(c);
			}
			if (g) {

				std::shared_ptr<GameObject> c = std::make_shared<GameObject>(cube);
				c->position.x = (x / 4);
				c->position.z = z;
				c->position.y = 1;
				addGameObject(c);
			}
			if (b) {
				std::shared_ptr<GameObject> c = std::make_shared<GameObject>(cube);
				c->position.x = (x / 4);
				c->position.z = z;
				c->position.y = 2;
				addGameObject(c);
			}
		}
	}
}