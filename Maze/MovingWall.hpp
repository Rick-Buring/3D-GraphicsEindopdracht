#pragma once

#include "InteractableGameObject.hpp"
#include "glm/glm.hpp"

class MovingWall : public InteractableGameObject {
private:
	glm::vec3 _moveTo;

public:
	MovingWall(std::shared_ptr<std::vector<Model3D_t>> model, glm::vec3 moveTo);


	// Inherited via InteractableGameObject
	virtual void interact(bool interacted) override;

};