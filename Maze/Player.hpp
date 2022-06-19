#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
public:
	Player(std::shared_ptr<std::vector<Model3D_t>>);

	// Inherited via GameObject

	/// <summary>
	/// function used to pull keyboard inputs and update player position accordingly
	/// </summary>
	/// <param name="deltaTime">time passed since last update.</param>
	virtual void update(float deltaTime) override;
};