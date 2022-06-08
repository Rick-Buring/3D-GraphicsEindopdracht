#include "MovingWall.hpp"

#include "glmUtils.hpp"

const float movingSpeed = 1.5;
MovingWall::MovingWall(std::shared_ptr<std::vector<Model3D_t>> model, glm::vec3 moveTo) : InteractableGameObject(model), _moveTo(moveTo)
{
	_targetPos = GameObject::position;
}

void MovingWall::interact(bool interacted)
{
	//if (interacted) {
	//	GameObject::position += _moveTo;
	//}else {
	//	GameObject::position -= _moveTo;
	//}

	//same as above but absurdly done
	_targetPos += _moveTo * (((interacted + 1) * 2) - 3);
}

void MovingWall::update(float deltaTime)
{
	glm::vec3 delta = MovingWall::_targetPos - GameObject::position;
	//check if we arrived
	if (glm::length(delta) < 0.01) {
		GameObject::position = MovingWall::_targetPos;
		return;
	}

  	GameObject::position += glm::normalize(delta) * (movingSpeed * deltaTime);

}
