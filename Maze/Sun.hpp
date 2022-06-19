#pragma once
#include "GameObject.hpp"
#include "LightManager.hpp"

class Sun : public GameObject {
private:
	lightInfo _sunLight;
	float _angle = 0;
	float _rotationSpeed = 36;

public:
	Sun(std::shared_ptr<std::vector<Model3D_t>>);
	~Sun();

	/// <summary>
	/// updates the object possition smootly with a constand speed.
	/// </summary>
	/// <param name="deltaTime">time passed since last update</param>
	void update(float deltaTime) override;

};