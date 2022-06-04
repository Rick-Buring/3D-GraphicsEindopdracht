#include "ThirdPersonCamera.hpp"
#include "glfwManager.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

ThirdPersonCamera::ThirdPersonCamera(GameObject* subject) : GameObject(nullptr), _subject(subject)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void ThirdPersonCamera::update(float deltaTime)
{

	double xPos = 0, yPos = 0;
	glfwGetCursorPos(window, &xPos, &yPos);
	rotation.y += (xPos - ThirdPersonCamera::xPosOld) / 10;
	rotation.x += (yPos - ThirdPersonCamera::yPosOld) / 10;

	ThirdPersonCamera::xPosOld = xPos;
	ThirdPersonCamera::yPosOld = yPos;

	//rotate player according to camera
	_subject->rotation.y = -glm::radians(rotation.y) + glm::radians(180.0f);

	glm::mat4 ret(1.0f);
	ret = glm::translate(ret, glm::vec3(0, 0, -ThirdPersonCamera::_distanceToSubject));
	ret = glm::rotate(ret, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	ret = glm::translate(ret, -_subject->position - glm::vec3(0, 1, 0));

	tigl::shader->setViewMatrix(ret);
}
