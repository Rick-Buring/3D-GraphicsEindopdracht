#pragma once

#include "GameObject.hpp"
#include "tigl.h"

class LoadScreen {
public:
	Texture* texture;

	LoadScreen(Texture* texture);
	void draw();
private:
	tigl::VBO* _plane;
};