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
	//tigl::shader->enableLighting(true); 
	//tigl::shader->enableColorMult(true);

	//static float dirX = 0, dirY = 0, dirZ = 0;

	//tigl::shader->setLightCount(1);
	//tigl::shader->setLightDirectional(0, true);
	//tigl::shader->setLightPosition(0, glm::vec3(dirX, dirY, dirZ));
	//tigl::shader->setLightAmbient(0, glm::vec3(1, 1, 1));

	static float lookX = -3, lookY = 4, lookZ = 0;




	ImGui::Begin("DebugWindow");
	ImGui::SliderFloat("lookX", &lookX, -12, 12.0f);
	ImGui::SliderFloat("lookY", &lookY, -12, 12.0f);
	ImGui::SliderFloat("lookZ", &lookZ, -12, 12.0f);

	//ImGui::SliderFloat("dirX", &dirX, -12, 12.0f);
	//ImGui::SliderFloat("dirY", &dirY, -12, 12.0f);
	//ImGui::SliderFloat("dirZ", &dirZ, -12, 12.0f);
	ImGui::End();
	
	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(lookX, lookY, lookZ), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	
	tigl::shader->enableColor(true);

	tigl::begin(GL_TRIANGLES);

	glm::vec4 col = glm::vec4(1, 1, 1, 1);

	tigl::addVertex(tigl::Vertex::PCN(glm::vec3(-1, 0, -1), col, glm::vec3(0, 1, 0)));
	tigl::addVertex(tigl::Vertex::PCN(glm::vec3(-1, 0, 1), col, glm::vec3(0, 1, 0)));
	tigl::addVertex(tigl::Vertex::PCN(glm::vec3(1, 0, -1), col, glm::vec3(0, 1, 0)));


	tigl::addVertex(tigl::Vertex::PCN(glm::vec3(1, 0, -1), col, glm::vec3(0, 1, 0)));
	tigl::addVertex(tigl::Vertex::PCN(glm::vec3(1, 0, 1), col, glm::vec3(0, 1, 0)));
	tigl::addVertex(tigl::Vertex::PCN(glm::vec3(-1, 0, 1), col, glm::vec3(0, 1, 0)));

	tigl::end();

	for (auto gameObject : _gameObjects) {
		gameObject->draw();
	}
}

void Scene::update()
{
	//calculate time passed since last frame
	double currentFrameTime = glfwGetTime();
	double deltaTime = currentFrameTime - Scene::_lastFrameTime;

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
	std::shared_ptr<std::vector<Model3D_t>> steve = loadObject("models/steve/steve.obj");
	std::shared_ptr<GameObject> player = std::make_shared<Player>(steve);

	std::shared_ptr<std::vector<Model3D_t>> plane = createPlane(1, 1);
	
	std::shared_ptr<GameObject> ground = std::make_shared<GameObject>(plane);

	std::shared_ptr<GameObject> leftWall = std::make_shared<GameObject>(plane);
	leftWall->rotation.z = M_PI / 2.0f;
	leftWall->position.x = 1;
	leftWall->position.y = 1;

	std::shared_ptr<GameObject> rightWall = std::make_shared<GameObject>(plane);
	rightWall->rotation.x = M_PI / 2.0f;
	rightWall->position.x = -1;
	rightWall->position.y = 1;

	std::shared_ptr<GameObject> behindWall = std::make_shared<GameObject>(plane);
	behindWall->rotation.x = M_PI / 2.0f;
	behindWall->position.z = -1;
	behindWall->position.y = 1;

	std::shared_ptr<GameObject> frontWall = std::make_shared<GameObject>(plane);
	frontWall->rotation.z = M_PI / 2.0f;
	frontWall->position.z = 1;
	frontWall->position.y = 1;


	//addGameObject(ground);
	//addGameObject(leftWall);
	//addGameObject(rightWall);
	//addGameObject(behindWall);
	//addGameObject(frontWall);

	//Todo create player
	//Todo create basic scene
}


