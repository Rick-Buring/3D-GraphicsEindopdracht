#include "Button.hpp"
#include "glfwManager.hpp"

const int ClickDelay = 2;

Button::Button(std::shared_ptr<std::vector<Model3D_t>> model, GameObject* player) : GameObject(model), _player(player)
{
	//todo get reffrence for a light
	_interacted = false;
	_lastClicked = ClickDelay;
}

void Button::update(float deltaTime)
{
	//function lock to prevent accidental double click
	if (_lastClicked < ClickDelay) {
		_lastClicked += deltaTime;
		return;
	}

	glm::vec3 dif = Button::_player->position - GameObject::position;
	float distance = glm::length(dif);
	
	if (distance < 1) {

		if (glfwGetKey(window, GLFW_KEY_E)) {
			_interacted = !_interacted;
			_lastClicked = 0;
		}
	}

}

void Button::draw()
{
	GameObject::draw();

	//todo add light emiting thing

}
