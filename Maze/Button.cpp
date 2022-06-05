#include "Button.hpp"
#include "glfwManager.hpp"

const int ClickDelay = 1;

Button::Button(std::shared_ptr<std::vector<Model3D_t>> model, GameObject* player, glm::vec3 p) : GameObject(model), _player(player)
{
	//set gameobject position
	GameObject::position = p;

	//initialize default values
	_interacted = false;
	_lastClicked = ClickDelay;

	//create light with color red
	light = lightInfo();
	light.isDirectional = false;
	light.position = p;
	light.ambient = glm::vec3(1, 0, 0);
	light.diffusion = glm::vec3(1, 0, 0);
	light.specular = glm::vec3(1);

	//addlight to the scene
	addLight(&light);
}

Button::~Button()
{
	removeLight(&light);
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
			if (_interacted) {
				light.ambient = glm::vec3(0, 1, 0);
				light.diffusion = glm::vec3(0, 1, 0);
			}
			else {
				light.ambient = glm::vec3(1, 0, 0);
				light.diffusion = glm::vec3(1, 0, 0);
			}
			light.setLight();

		}
	}

}

void Button::draw()
{
	GameObject::draw();
}
