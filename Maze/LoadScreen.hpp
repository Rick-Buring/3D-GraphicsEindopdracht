#pragma once

#include "GameObject.hpp"
#include "tigl.h"

class LoadScreen : public GameObject {
public:

	LoadScreen(std::vector<Texture*> textures);
	void draw() override;
	void update(float deltaTime) override;
private:
	std::vector<Texture*> _textures;
	float _currentTexture;
	tigl::VBO* _plane;
};