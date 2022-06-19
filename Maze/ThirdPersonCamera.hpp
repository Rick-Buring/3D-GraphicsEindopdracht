#pragma once
#include "GameObject.hpp"

class ThirdPersonCamera : public GameObject {
public:
	float _distanceToSubject = 2;
	double xPosOld = 0, yPosOld = 0;

	GameObject* _subject;

	ThirdPersonCamera();
	~ThirdPersonCamera();

	void setSubject(GameObject* subject);

	//inherided from GameObject
	void update(float deltaTime) override;
	void draw() override;
};