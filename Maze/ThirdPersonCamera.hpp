#pragma once
#include "GameObject.hpp"

class ThirdPersonCamera : public GameObject {
private:
	float _distanceToSubject = 2;
	double _xPosOld = 0, _yPosOld = 0;
	GameObject* _subject;

public:


	ThirdPersonCamera();
	~ThirdPersonCamera();

	/// <summary>
	/// setter function
	/// </summary>
	/// <param name="subject">pointer to object to focus on</param>
	void setSubject(GameObject* subject);

	//inherided from GameObject

	/// <summary>
	/// pulls mouse inputs and updates the camera position accordingly
	/// </summary>
	/// <param name="deltaTime">time passed since last update</param>
	void update(float deltaTime) override;

	/// <summary>
	/// empty implementation of draw function to some resouces
	/// </summary>
	void draw() override;
};