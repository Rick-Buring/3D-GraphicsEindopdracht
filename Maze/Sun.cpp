#include "Sun.hpp"
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/color_space.hpp>
#include "glmUtils.hpp"

const float twoPi = (2 * glm::pi<float>()), distance = 100;
const short int hueOffset = 240, hueRange = 180, hueMax = 360;

Sun::Sun(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model)
{
	position = calculatePosition(_angle) * 10;

	_sunLight = lightInfo();
	_sunLight.isDirectional = true;
	_sunLight.specular = glm::vec3(1);

	_sunLight.position = glm::normalize(position);
	_sunLight.diffusion = glm::vec3(0.3f);

	addLight(&_sunLight);
}

Sun::~Sun()
{
	removeLight(&_sunLight);
}


void Sun::update(float deltaTime)
{


	_angle += deltaTime / Sun::_rotationSpeed;

	//prevent overflow
	_angle = fmod(Sun::_angle, twoPi);

	_sunLight.position = calculatePosition(_angle);

	//formula for calculating infinate hue scrolling based on y value
	//hueOffset is the hue if y pos is at its lowest
	//y pos + 1 because y min = sin(270) = -1
	//hueRange is the diffrent possible hue values to go by in the range y min - y max 
	//hueRange gets divided by 2 becase y min = -1 y max = 1 y delta = 2
	//modulo huemax to allow continuous scrolling
	//make range negative for revese scroling
	float hue = fmod(hueOffset + (_sunLight.position.y + 1) * (hueRange / 2), hueMax);

	_sunLight.ambient = glm::normalize(glm::rgbColor(glm::vec3(hue, 0.2, 1)));
	_sunLight.setLight();

	GameObject::position = _sunLight.position * distance;

}
