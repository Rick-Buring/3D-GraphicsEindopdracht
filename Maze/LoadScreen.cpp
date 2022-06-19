#include "LoadScreen.hpp"

#include <vector>
#include "Texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "glfwManager.hpp"

constexpr glm::vec3 s = glm::vec3(2, 2, 0);
constexpr glm::vec4 color = glm::vec4(1);
constexpr float TimeBetweenLoadScreenImages = 2.0f;

LoadScreen::LoadScreen(std::vector<Texture*> textures) : GameObject(nullptr), _textures(textures)
{
	_currentTexture = 0;
	std::vector<tigl::Vertex> vertexBuffer = std::vector<tigl::Vertex>();

	vertexBuffer.push_back(tigl::Vertex::PCTN(glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PCTN(glm::vec3(-s.x, s.y, s.z), color, glm::vec2(s.x, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PCTN(glm::vec3(s.x, s.y, s.z), color, glm::vec2(s.x, s.y), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PCTN(glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PCTN(glm::vec3(s.x, s.y, s.z), color, glm::vec2(s.x, s.y), glm::vec3(0, 0, 1)));
	vertexBuffer.push_back(tigl::Vertex::PCTN(glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, s.y), glm::vec3(0, 0, 1)));

	_plane = tigl::createVbo(vertexBuffer);


}

void LoadScreen::draw()
{
	tigl::shader->enableTexture(true);
	LoadScreen::_textures.at(((int)_currentTexture) % _textures.size())->bind();

	int width = 10, height = 10;

	glm::mat4 projection = glm::ortho(0.0f, s.x, s.y, 0.0f, 1.0f, 10.0f);
	tigl::shader->setProjectionMatrix(projection);

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 0, -4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	tigl::shader->setViewMatrix(viewMatrix);

	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::drawVertices(GL_TRIANGLES, _plane);
	Texture_unbind();
	tigl::shader->enableTexture(false);
}

void LoadScreen::update(float deltaTime)
{
	_currentTexture += (deltaTime / TimeBetweenLoadScreenImages);
	if (_currentTexture > _textures.size()) {
		_currentTexture = 0;
	}
}
