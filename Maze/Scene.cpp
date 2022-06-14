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

typedef std::vector<std::vector<std::vector<std::shared_ptr<GameObject>>>> yzxGameObject;

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

	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	glEnable(GL_DEPTH_TEST);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0), glm::vec3(0, 1, 0)));

	for (auto& gameObject : _gameObjects) {
		gameObject->draw();
	}
	if (_player) {
		_player->draw();
	}
}
bool loading = false;

Scene::Scene()
{
	_camera = std::make_shared<ThirdPersonCamera>();
	_loadScreen = std::make_shared<LoadScreen>(new Texture("resources\\modelsv1\\wall\\Rock037_4K_Color.jpg"));
	addGameObject(_loadScreen);
	loading = true;
	//loadLevel("resources/levels/firstData.txt");
}
void Scene::update()
{
	if (loading) {
		draw();
		return;
	}

	//calculate time passed since last frame
	double currentFrameTime = glfwGetTime();
	float deltaTime = (float)(currentFrameTime - Scene::_lastFrameTime);
	_lastFrameTime = currentFrameTime;

	//update logic
	for (auto& gameObject : Scene::_gameObjects) {
		gameObject->update(deltaTime);
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
	for (auto& obj : list) {
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
	//create copy for live reload
	std::string localPathCopy = path.c_str();

	//reset scene
	reset();

	//standart objects
	std::shared_ptr<std::vector<Model3D_t>> cube = buildCube(glm::vec3(0), glm::vec3(0.5), glm::vec4(1));
	std::shared_ptr<std::vector<Model3D_t>> sphere = buildSphere(glm::vec3(0), glm::vec3(0.5), glm::vec4(1));

	//load file with factory patern 
	std::string filePath = localPathCopy;
	AbstractLevelDataReader* reader = getReader(filePath);
	std::vector<LevelData_t> levelData = reader->readData(filePath);

	//load 3d models
	auto models = loadObjects(levelData[0].path);

	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(findModel("wall", models));
	addGameObject(gameObject);
	std::shared_ptr<GameObject> gameObject2 = std::make_shared<GameObject>(cube);
	gameObject2->position.x = 1;
	addGameObject(gameObject2);

	//load maze image
	std::string mazePath = levelData[1].path;
	auto maze = loadMazeFromImage(mazePath, models, cube);

	for (size_t i = 2; i < levelData.size(); i++)
	{
		levelData_st data = levelData[i].data;
		std::string dataType = data.type;

		if (dataType == "player") {
			//only one player per level
			if (_player)
				continue;

			_player = std::make_shared<Player>(findModel("player", models));
			_player->scale = glm::vec3(0.1f);
			_player->position = data.position;
			_player->position.y -= 0.5f;

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

			//validate vecor range
			if (data.Linkedposition.y > -1 && data.Linkedposition.y < maze.size() &&
				data.Linkedposition.z > -1 && data.Linkedposition.z < maze[(__int64)data.Linkedposition.y].size() &&
				data.Linkedposition.x > -1 && data.Linkedposition.x < maze[(__int64)data.Linkedposition.y][(__int64)data.Linkedposition.z].size()) {

				std::shared_ptr<GameObject> gameObject = maze[(__int64)data.Linkedposition.y][(__int64)data.Linkedposition.z][(__int64)data.Linkedposition.x];
				std::shared_ptr<std::vector<Model3D_t>> model = gameObject ? gameObject->model : cube;
				glm::vec3 position = gameObject ? gameObject->position : data.Linkedposition;

				std::shared_ptr<InteractableGameObject> interactingObject =
					std::string(data.linkedWithType) == "moving_wall" ? std::make_shared<MovingWall>(model, position, data.action) :
					nullptr;

				interactingObject->rotation = gameObject ? gameObject->rotation : glm::vec3(0);
				addGameObject(interactingObject);

				auto butten = std::make_shared<Button>(cube, _player.get(), data.position, interactingObject.get());
				butten->scale = glm::vec3(.5f);
				addGameObject(butten);
			}
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

	//add maze to scene
	for (auto& y : maze) {
		for (auto& z : y) {
			for (auto& gameObject : z) {

				//check if gameObject at index
				if (gameObject) {
					addGameObject(gameObject);
				}
			}
		}
	}
}

yzxGameObject Scene::loadMazeFromImage(std::string mazePath, std::vector<NamedModel3D_t>& models, std::shared_ptr<std::vector<Model3D_t>>& cube)
{
	int width, height, bpp;
	unsigned char* image = stbi_load(mazePath.c_str(), &width, &height, &bpp, 4);

	yzxGameObject maze = yzxGameObject(3);

	maze[0] = std::vector<std::vector<std::shared_ptr<GameObject>>>(height); // y value
	maze[1] = std::vector<std::vector<std::shared_ptr<GameObject>>>(height); // y value
	maze[2] = std::vector<std::vector<std::shared_ptr<GameObject>>>(height); // y value

	for (size_t z = 0; z < height; z++)
	{
		maze[0][z] = std::vector<std::shared_ptr<GameObject>>(width); // z value
		maze[1][z] = std::vector<std::shared_ptr<GameObject>>(width); // z value
		maze[2][z] = std::vector<std::shared_ptr<GameObject>>(width); // z value

		for (int x4 = 0; x4 < width * 4; x4 += 4)
		{
			int x = x4 / 4;
			maze[0][z][x] = (nullptr); // x value
			maze[1][z][x] = (nullptr); // x value
			maze[2][z][z] = (nullptr); // x value

			//objects position is x y z
			//x is encoded in width of image
			//z is encoded in height of image
			//y is encoded in color channel of image
			//value in chanel is the index of the object to render
			unsigned char rgb[] = {
				image[z * height * 4 + x4 + 0],
				image[z * height * 4 + x4 + 1],
				image[z * height * 4 + x4 + 2]
			};

			//encoded value used for rotation 
			//         y2 y1 y0 **
			// example 11 10 01 11 = 270 degrees on y 2, 180 degrees on y 1, 90 degrees on y 0
			// example y0 270 y1 0 degrees y2 180 degrees = 10 00 11 11
			unsigned char a = image[z * height * 4 + x + 3];

			for (size_t y = 0; y < 3; y++) {
				if (rgb[y]) {
					std::shared_ptr<std::vector<Model3D_t>> model = rgb[y] == 0xff ? cube : models[rgb[y] % models.size()].model;
					std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(model);
					gameObject->position.x = (float)x;
					gameObject->position.z = (float)z;
					gameObject->position.y = (float)y;
					maze[y][z][x] = gameObject;
					char rotation = (a >> (y + 1)) & 0x3;
					gameObject->rotation.y = glm::radians(90.0f * rotation);
				}
			}
		}
	}
	return maze;
}