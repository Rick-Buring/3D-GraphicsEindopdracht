#include "Scene.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

#include "ObjectLoader.hpp"
#include "Player.hpp"
#include "imgui.h"

#define _USE_MATH_DEFINES

#include <math.h>

void Scene::draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	glEnable(GL_DEPTH_TEST);

	static float lookX = -3, lookY = 4, lookZ = 0;

	ImGui::Begin("DebugWindow");
	ImGui::SliderFloat("lookX", &lookX, -12, 12.0f);
	ImGui::SliderFloat("lookY", &lookY, -12, 12.0f);
	ImGui::SliderFloat("lookZ", &lookZ, -12, 12.0f);
	ImGui::End();
	
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

std::shared_ptr<std::vector<Model3D_t>> createPlane(float width, float height) {
	std::shared_ptr<std::vector<Model3D_t>> returnValue = std::make_shared<std::vector<Model3D_t>>();

	std::vector<tigl::Vertex> tempVertexes;

	glm::vec4 col = glm::vec4(1, 1, 1, 1);

	tempVertexes.push_back(tigl::Vertex::PCN(glm::vec3(-width, 0, -height), col, glm::vec3(0, 1, 0)));
	tempVertexes.push_back(tigl::Vertex::PCN(glm::vec3(-width, 0, height), col, glm::vec3(0, 1, 0)));
	tempVertexes.push_back(tigl::Vertex::PCN(glm::vec3(width, 0, -height), col, glm::vec3(0, 1, 0)));


	tempVertexes.push_back(tigl::Vertex::PCN(glm::vec3(width, 0, -height), col, glm::vec3(0, 1, 0)));
	tempVertexes.push_back(tigl::Vertex::PCN(glm::vec3(width, 0, height), col, glm::vec3(0, 1, 0)));
	tempVertexes.push_back(tigl::Vertex::PCN(glm::vec3(-width, 0, height), col, glm::vec3(0, 1, 0)));
	
	Model3D_t tempModel;
	tempModel.texture = nullptr;
	tempModel.vbo = tigl::createVbo(tempVertexes);
	
	returnValue->push_back(tempModel);

	return returnValue;
}

void Scene::initBaseScene()
{
	//todo create json file with all file locations for models aswel as the maze image
	//todo load all models 

	std::shared_ptr<std::vector<Model3D_t>> plane = createPlane(1, 1);

	//load maze image
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
			int a = image[z * height * 4 + x + 3];

			//todo create 3d objects based off decoded values
		}
	}
	
	//Todo create player need to decide if third person or first person view

	std::shared_ptr<std::vector<Model3D_t>> steve = loadObject("models/steve/steve.obj");
	std::shared_ptr<GameObject> player = std::make_shared<Player>(steve);
	player->scale = glm::vec3(0.2);
}


