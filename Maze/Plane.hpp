#pragma once

#include "GameObject.hpp"
#include "tigl.h"

class Plane : public GameObject {

private:
	tigl::VBO shape;

public:
	Plane(float height, float width);

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};