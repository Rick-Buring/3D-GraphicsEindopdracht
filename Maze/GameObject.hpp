#pragma once
#include <memory>

#include <glm/glm.hpp>
#include "ObjectLoader.hpp"

class GameObject {
protected:
	glm::mat4 _modelMatrix = glm::mat4(1.0f);

private:
	//model for drawing
	std::shared_ptr<std::vector<Model3D_t>> _model;

public:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);

	GameObject(std::shared_ptr<std::vector<Model3D_t>>);

	/// <summary>
	/// update called once every frame
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void update(float deltaTime);
	
	/// <summary>
	/// draw called everyframe contains draw functions for 3d objects
	/// </summary>
	virtual void draw();
};