#pragma once
#include "GameObject.hpp"
#include "lightManager.hpp"

class Button : public GameObject {
private:
	GameObject* _player;
	bool _interacted;
	double _lastClicked;
	lightInfo light;

public:
	Button(std::shared_ptr<std::vector<Model3D_t>>, GameObject*, glm::vec3 position);
	~Button();

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};