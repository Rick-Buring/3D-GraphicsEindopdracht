#pragma once
#include "GameObject.hpp"
#include "LightManager.hpp"

class Sun : public GameObject {
private:
	lightInfo _sunLight;
	float _angle = 0;
	float _rotationSpeed = 30;

public:
	Sun(std::shared_ptr<std::vector<Model3D_t>>);
	~Sun();

	void update(float deltaTime) override;

};