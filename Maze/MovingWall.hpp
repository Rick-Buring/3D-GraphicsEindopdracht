#pragma once

#include "InteractableGameObject.hpp"
#include "glm/glm.hpp"

class MovingWall : public InteractableGameObject {
private:
	glm::vec3 _moveTo;
	glm::vec3 _targetPos;

public:
	MovingWall(std::shared_ptr<std::vector<Model3D_t>> model, glm::vec3 position, glm::vec3 moveTo);


	// Inherited via InteractableGameObject

	/// <summary>
	/// when this is called the object moves to a new world position namely the _targetPos
	/// </summary>
	/// <param name="interacted">boolean to determen if the objects new position is plus or minus the _moveTo variable</param>
	virtual void interact(bool interacted) override;


	//inherited via GameObject
	
	/// <summary>
	/// updates the object possition smootly with a constand speed.
	/// </summary>
	/// <param name="deltaTime">time passed since last update</param>
	virtual void update(float deltaTime) override;

};