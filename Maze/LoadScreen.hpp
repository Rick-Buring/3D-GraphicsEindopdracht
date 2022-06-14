#pragma once

#include "GameObject.hpp"
#include "tigl.h"

class LoadScreen : public GameObject {
public:
	Texture* texture;

	LoadScreen(Texture* texture);
	void draw() override;
private:
	tigl::VBO* _plane;
};