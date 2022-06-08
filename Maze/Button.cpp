#include "Button.hpp"
#include "glfwManager.hpp"
#include "glmUtils.hpp"

const int ClickDelay = 1;
const glm::vec3 red = glm::vec3(0.4f, 0.25f, 0.25f) * 0.5, green= glm::vec3(0.25f, 0.4f, 0.25f)   ;
Button::Button(std::shared_ptr<std::vector<Model3D_t>> model, GameObject* player, glm::vec3 p, InteractableGameObject* interactableObj)
	: GameObject(model), _player(player), _interactableObj(interactableObj)
{
	//set gameobject position
	GameObject::position = p;

	//initialize default values
	_interacted = false;
	_lastClicked = ClickDelay;

	//create light with color red
	_light = lightInfo();
	_light.isDirectional = false;
	_light.position = p;
	_light.ambient = red;
	_light.diffusion = glm::vec3(0.2f);
	_light.specular = glm::vec3(1);

	//addlight to the scene
	//addLight(&_light);
}

Button::~Button()
{
	//removeLight(&_light);
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
			_lastClicked = 0;

			_interacted = !_interacted;
			if (_interacted) {
				_light.ambient = green;
			}
			else {
				_light.ambient = red;
			}
			//update light
			//_light.setLight();

			if (_interactableObj) {
				_interactableObj->interact(_interacted);
			}
		}
	}

}

void Button::draw()
{
	GameObject::draw();
}
