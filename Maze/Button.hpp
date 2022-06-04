#pragma once
#include "GameObject.hpp"

class Button : public GameObject {
private:
	GameObject* _player;
	bool _interacted;
	double _lastClicked;

public:
	Button(std::shared_ptr<std::vector<Model3D_t>>, GameObject*);

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};