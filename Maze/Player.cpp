#include "Player.hpp"
#include "Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/matrix_decompose.hpp>

Player::Player(std::shared_ptr<std::vector<Model3D_t>> model ) : GameObject(model)
{
}

void Player::update(float deltaTime)
{
}

void Player::draw()
{
	GameObject::draw();

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, GameObject::position);
	modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.y + glm::pi<float>() / 2, glm::vec3(0, 1, 0));

	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 2, -3));

	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(modelMatrix, scale, rotation, translation, skew, perspective);

	glm::mat4 view = glm::lookAt(translation, position, glm::vec3(0, 1, 0));


	tigl::shader->setViewMatrix(view);
	GameObject::draw();

}
