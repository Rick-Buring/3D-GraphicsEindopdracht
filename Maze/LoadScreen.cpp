#include "LoadScreen.hpp"

#include <vector>
#include "Texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "glfwManager.hpp"

LoadScreen::LoadScreen(Texture* texture) : GameObject(nullptr), texture(texture)
{
	std::vector<tigl::Vertex> vertexBuffer = std::vector<tigl::Vertex>();

	vertexBuffer.push_back(tigl::Vertex::PT(glm::vec3(500, 500, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PT(glm::vec3(500, -500, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PT(glm::vec3(-500, 500, 0), glm::vec3(0, 0, 1)));

	vertexBuffer.push_back(tigl::Vertex::PT(glm::vec3(-500, 500, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PT(glm::vec3(-500, -500, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PT(glm::vec3(500, -500, 0), glm::vec3(0, 0, 1)));

	_plane = tigl::createVbo(vertexBuffer);
}

void LoadScreen::draw()
{
	tigl::shader->enableTexture(true);
	LoadScreen::texture->bind();

	int width = 10, height = 10;
	glfwGetWindowSize(window, &width, &height);

	glm::mat4 projection = glm::ortho<float>(0, 0, width, height, 0.01f, 5.0f);

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	tigl::shader->setViewMatrix(viewMatrix);
	glm::mat4 modelMatrix = glm::mat4(1);
	tigl::shader->setModelMatrix(modelMatrix);

	tigl::shader->setProjectionMatrix(projection);

	tigl::drawVertices(GL_TRIANGLES, _plane);
	TextureUnbind();
	tigl::shader->enableTexture(false);
}
