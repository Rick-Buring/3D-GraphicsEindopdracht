#pragma once
#include <memory>

#include <glm/glm.hpp>
#include "ObjectLoader.hpp"

class GameObject {
protected:
	glm::mat4 _modelMatrix = glm::mat4(1.0f);

public:
	//World relative position rotation and scale used to calculate modelMatrix
	glm::vec3 Position = glm::vec3(0);
	glm::vec3 Rotation = glm::vec3(0);
	glm::vec3 Scale = glm::vec3(1);

	//model for drawing
	std::shared_ptr<std::vector<Model3D_t>> Model;

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