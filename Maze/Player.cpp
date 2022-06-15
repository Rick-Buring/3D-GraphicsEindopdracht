#include "Player.hpp"
#include "Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/matrix_decompose.hpp>
#include "glfwManager.hpp"

//const glm::vec3 forwards = glm::vec3(0, 0, 1), backwards = glm::vec3(0, 0, -1), left = glm::vec3(-1, 0, 0), right = glm::vec3(1, 0, 0);
const float walkSpeed = 30;

Player::Player(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model)
{
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Player::~Player()
{
}


void Player::update(float deltaTime)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
		return;
	}
	glm::vec3 move = glm::vec3(0);

	//update move vector with key directions
	move.z += glfwGetKey(window, GLFW_KEY_W);			//move forward
	move.z -= glfwGetKey(window, GLFW_KEY_S);			//move backward
	move.x += glfwGetKey(window, GLFW_KEY_A);			//move left
	move.x -= glfwGetKey(window, GLFW_KEY_D);			//move right
	move.y += glfwGetKey(window, GLFW_KEY_SPACE);		//move up
	move.y -= glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);	//move down

	//check if we move
	if (move.x || move.z || move.y) {

		move = glm::normalize(move);
		move = move * walkSpeed * deltaTime;

		//translate local forward to world direction
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		//modelMatrix = glm::translate(modelMatrix, GameObject::position);
		modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.y + glm::radians<float>(90), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.z, glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, GameObject::scale);
		modelMatrix = glm::translate(modelMatrix, move);

		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(modelMatrix, scale, rotation, move, skew, perspective);


		GameObject::position += move;
	}

}

void Player::draw()
{
	GameObject::draw();
}
