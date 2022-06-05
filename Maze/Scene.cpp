#include "Scene.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

#include "ObjectLoader.hpp"
#include "Player.hpp"
#include "imgui.h"
#include "utills.hpp"

#define _USE_MATH_DEFINES

#include <math.h>
#include "stb_image.h"
#include "ThirdPersonCamera.hpp"
#include "Button.hpp"

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
}

void Scene::update()
{
	//calculate time passed since last frame
	double currentFrameTime = glfwGetTime();
	double deltaTime = currentFrameTime - Scene::_lastFrameTime;
	_lastFrameTime = currentFrameTime;

	//todo update scene time and sun location

	//update logic
	for (auto gameObject : Scene::_gameObjects) {
		gameObject->update((float)deltaTime);
	}

	//redraw scene
	this->draw();
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	this->_gameObjects.push_back(gameObject);
}

void Scene::initBaseScene()
{
	//todo create json file with all file locations for models aswel as the maze image
	//todo load all models 
	std::shared_ptr<std::vector<Model3D_t>> cube = buildCube(glm::vec3(0), glm::vec3(0.5), glm::vec4(2));

	//load maze image
	//loadMazeFromFile(cube);

	std::shared_ptr<std::vector<Model3D_t>> steve = loadObject("models/steve/steve.obj");
	std::shared_ptr<GameObject> player = std::make_shared<Player>(steve);
	player->scale = glm::vec3(0.2f);
	addGameObject(player);

	std::shared_ptr<GameObject> camera = std::make_shared<ThirdPersonCamera>(player.get());
	addGameObject(camera);

	//std::shared_ptr<GameObject> button = std::make_shared<Button>(cube, player.get(), glm::vec3(0.5));
	//button->scale = glm::vec3(0.2f);
	//addGameObject(button);


}

void Scene::loadMazeFromFile(std::shared_ptr<std::vector<Model3D_t>>& cube)
{
	int width, height, bpp;
	unsigned char* image = stbi_load("resouces\\mazes\\Maze.png", &width, &height, &bpp, 4);

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


