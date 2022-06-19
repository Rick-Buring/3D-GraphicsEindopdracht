#pragma once

#include "GameObject.hpp"

/// <summary>
/// abstract interface class
/// </summary>
class InteractableGameObject : public GameObject {
public:
	InteractableGameObject(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model) {};

	/// <summary>
	/// function called when this object is interacted with
	/// </summary>
	/// <param name="interacted"></param>
	virtual void interact(bool interacted) = 0;
};