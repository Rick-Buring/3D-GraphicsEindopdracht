#include "LoadScreen.hpp"

#include <vector>
#include "Texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "glfwManager.hpp"

LoadScreen::LoadScreen(Texture* texture) : texture(texture)
{
	std::vector<tigl::Vertex> vertexBuffer = std::vector<tigl::Vertex>();

	vertexBuffer.push_back(tigl::Vertex::PN(glm::vec3(1, 1, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PN(glm::vec3(1, -1, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PN(glm::vec3(-1, 1, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PN(glm::vec3(-1, -1, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PN(glm::vec3(1, -1, 0), glm::vec3(0, 0, 1)));

	_plane = tigl::createVbo(vertexBuffer);
}

void LoadScreen::draw()
{
	LoadScreen::texture->bind();

	int width = 10, height = 10;
	//glfwGetWindowSize(window, &width, &height);

	glm::mat4 projection = glm::ortho<float>(0, 0, width, height, 0.01f, 5.0f);

	tigl::shader->setProjectionMatrix(projection);

	tigl::drawVertices(GL_TRIANGLES, _plane);
	TextureUnbind();
}
