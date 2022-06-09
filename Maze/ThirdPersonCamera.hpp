#pragma once
#include "GameObject.hpp"

class ThirdPersonCamera : public GameObject {
public:
	float _distanceToSubject = 5;
	double xPosOld = 0, yPosOld = 0;

	GameObject* _subject;

	ThirdPersonCamera();

	void setSubject(GameObject* subject);

	void update(float deltaTime) override;
};