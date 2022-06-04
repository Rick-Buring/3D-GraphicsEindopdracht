#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

#include "GameObject.hpp"
#include "Texture.hpp"


GameObject::GameObject(std::shared_ptr<std::vector<Model3D_t>> model) : _model(model)
{
}

void GameObject::update(float deltaTime)
{

}

void GameObject::draw()
{
	if (_model == nullptr)
		return;

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, GameObject::position);
	modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, GameObject::rotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, GameObject::scale);

	tigl::shader->setModelMatrix(modelMatrix);

	for (auto model : *_model) {
		if (model.texture) {
			tigl::shader->enableTexture(true);
			model.texture->bind(); 
			tigl::drawVertices(GL_TRIANGLES, model.vbo);
			tigl::shader->enableTexture(false);
		}
		tigl::drawVertices(GL_TRIANGLES, model.vbo);		
	}
}
