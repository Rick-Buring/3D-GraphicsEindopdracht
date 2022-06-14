#include "ThirdPersonCamera.hpp"
#include "glfwManager.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

ThirdPersonCamera::ThirdPersonCamera() : GameObject(nullptr)
{
	_subject = nullptr;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

ThirdPersonCamera::~ThirdPersonCamera()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void ThirdPersonCamera::setSubject(GameObject* subject)
{
	_subject = subject;
	GameObject::position = glm::vec3(0, 0, -ThirdPersonCamera::_distanceToSubject);
}

void ThirdPersonCamera::update(float deltaTime)
{
	//check if mouse is visable if it is return so user can freely use his mouse
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
		return;
	}
	double xPos = 0, yPos = 0;
	glfwGetCursorPos(window, &xPos, &yPos);
	
	//calculate delta for mouse and add to current rotation 
	rotation.y += (float) (xPos - ThirdPersonCamera::xPosOld) / 10.0f;
	rotation.x += (float) (yPos - ThirdPersonCamera::yPosOld) / 10.0f;
	
	//reset values
	ThirdPersonCamera::xPosOld = xPos;
	ThirdPersonCamera::yPosOld = yPos;

	//rotate player according to camera
	_subject->rotation.y = -glm::radians(rotation.y) + glm::radians(90.0f);

	//calculate camera position
	glm::mat4 ret(1.0f);
	ret = glm::translate(ret, GameObject::position);
	ret = glm::rotate(ret, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	ret = glm::translate(ret, -_subject->position - glm::vec3(0, 0.5, 0));

	//set new view position
	tigl::shader->setViewMatrix(ret);
}
