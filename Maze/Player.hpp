#pragma once
#include "GameObject.hpp"
#include "ObjectLoader.hpp"
#include <memory>

class Player : public GameObject {
private:
	std::vector<Model3D_t> _model;

public:
	Player(std::vector<Model3D_t>);

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};