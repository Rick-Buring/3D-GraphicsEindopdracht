#pragma once
#include "GameObject.hpp"
#include "ObjectLoader.hpp"
#include <memory>

class Player : public GameObject {
private:
	std::shared_ptr<Model3D_t> _model;

public:
	Player(std::shared_ptr<Model3D_t>);

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};