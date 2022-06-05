#include "Sun.hpp"
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/color_space.hpp>

const float twoPi = (2 * glm::pi<float>());
static glm::vec3 calculatePosition(float angle) {
	return glm::vec3(glm::cos(angle), glm::sin(angle), glm::cos(angle));
}

glm::vec3 operator*(const glm::vec3& v1, const float& v2) {
	return glm::vec3(v1.x * v2, v1.y * v2, v1.z * v2);
}

Sun::Sun(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model)
{
	position = calculatePosition(_angle) * 10;

	_sunLight = lightInfo();
	_sunLight.isDirectional = true;
	_sunLight.specular = glm::vec3(1);

	_sunLight.position = glm::normalize(position);
	_sunLight.ambient = glm::vec3(0.5f);
	_sunLight.diffusion = glm::vec3(0.5f);

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

	//magic formula for calculating hue based on y pos 
	float hue = fmod(240 + (1 + _sunLight.position.y) * 90, 360);

 	_sunLight.ambient = glm::rgbColor(glm::vec3(hue, 0.2, 1));
	_sunLight.setLight();

	GameObject::position = _sunLight.position * 10;

}
