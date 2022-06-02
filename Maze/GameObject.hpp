#pragma once
#include <glm/glm.hpp>

class GameObject {
private:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);

public:
	/// <summary>
	/// update called once every frame
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void update(float deltaTime) = 0;
	
	/// <summary>
	/// draw called everyframe contains draw functions for 3d objects
	/// </summary>
	virtual void draw();
};