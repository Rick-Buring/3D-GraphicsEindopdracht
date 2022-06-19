#include "ThirdPersonCamera.hpp"
#include "glfwManager.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

ThirdPersonCamera::ThirdPersonCamera() : GameObject(nullptr)
{
	_subject = nullptr;
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

ThirdPersonCamera::~ThirdPersonCamera()
{
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void ThirdPersonCamera::setSubject(GameObject* subject)
{
	_subject = subject;
	GameObject::Position = glm::vec3(0, 0, -ThirdPersonCamera::_distanceToSubject);
}

void ThirdPersonCamera::update(float deltaTime)
{
	//check if mouse is visable if it is return so user can freely use his mouse
	if (glfwGetInputMode(Window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
		return;
	}
	double xPos = 0, yPos = 0;
	glfwGetCursorPos(Window, &xPos, &yPos);
	
	//calculate delta for mouse and add to current rotation 
	Rotation.y += (float) (xPos - ThirdPersonCamera::_xPosOld) / 10.0f;
	Rotation.x += (float) (yPos - ThirdPersonCamera::_yPosOld) / 10.0f;
	
	//reset values
	ThirdPersonCamera::_xPosOld = xPos;
	ThirdPersonCamera::_yPosOld = yPos;

	//rotate player according to camera
	_subject->Rotation.y = -glm::radians(Rotation.y) + glm::radians(90.0f);

	//calculate camera position
	glm::mat4 ret(1.0f);
	ret = glm::translate(ret, GameObject::Position);
	ret = glm::rotate(ret, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	ret = glm::translate(ret, -_subject->Position - glm::vec3(0, 0.5, 0));

	//set new view position
	tigl::shader->setViewMatrix(ret);
}

void ThirdPersonCamera::draw()
{
}
