#include "MovingWall.hpp"

#include "glmUtils.hpp"

MovingWall::MovingWall(std::shared_ptr<std::vector<Model3D_t>> model, glm::vec3 moveTo) : InteractableGameObject(model), _moveTo(moveTo)
{
}

void MovingWall::interact(bool interacted)
{
	//if (interacted) {
	//	GameObject::position += _moveTo;
	//}else {
	//	GameObject::position -= _moveTo;
	//}

	//same as above but absurdly done
	GameObject::position += _moveTo * (((interacted + 1) * 2) - 3);
}
