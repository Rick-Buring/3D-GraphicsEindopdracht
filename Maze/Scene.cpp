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

typedef std::vector<std::vector<std::vector<std::shared_ptr<GameObject>>>> yzxGameObject;

bool loading = false;

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

	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	glEnable(GL_DEPTH_TEST);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	for (auto& gameObject : _gameObjects) {
		gameObject->draw();
	}
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
	_camera->setSubject(_player.get());
}
#pragma region TODO Move to new file


void Scene::loadLevel(const std::string& path)
{
	//create copy for live reload
	std::string localPathCopy = path.c_str();

	//reset scene
	reset();

	LoadNewScene(*this, localPathCopy);

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
#pragma endregion
