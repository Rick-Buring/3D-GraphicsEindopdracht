#pragma once

#include "GameObject.hpp"

class InteractableGameObject : public GameObject {
public:
	InteractableGameObject(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model) {};
	virtual void interact(bool interacted) = 0;
};