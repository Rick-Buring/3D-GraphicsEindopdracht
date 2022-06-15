#pragma once

#include "GameObject.hpp"

class InteractableGameObject : public GameObject {
public:
	InteractableGameObject(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model) = 0;
	virtual void interact(bool interacted) = 0;
};