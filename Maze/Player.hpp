#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
private:

public:
	Player(std::shared_ptr<std::vector<Model3D_t>>);
	~Player();

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};