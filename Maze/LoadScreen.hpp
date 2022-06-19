#pragma once

#include "GameObject.hpp"
#include "tigl.h"

class LoadScreen : public GameObject {
private:
	std::vector<Texture*> _textures;
	float _currentTexture;
	tigl::VBO* _plane;

public:
	LoadScreen(std::vector<Texture*> textures);

	//inhareted functions from gameObject
	
	/// <summary>
	/// draws the loading screen this takes over the current draw context and fills the screen. 
	/// if there is an object in the scene that is within the bounds of the camera placement in this draw method the objects will stil be visable
	/// </summary>
	void draw() override;

	/// <summary>
	/// updatefunction used to switch textures for dynamicly showing diffrent loadingscreens
	/// </summary>
	/// <param name="deltaTime">time passed since last frame</param>
	void update(float deltaTime) override;

};