#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

#include "GameObject.hpp"
#include "Texture.hpp"


GameObject::GameObject(std::shared_ptr<std::vector<Model3D_t>> model) : Model(model)
{
}

void GameObject::update(float deltaTime)
{
}

void GameObject::draw()
{
	if (!Model)
		return;

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, GameObject::Position);
	modelMatrix = glm::rotate(modelMatrix, GameObject::Rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, GameObject::Rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, GameObject::Rotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, GameObject::Scale);

	tigl::shader->setModelMatrix(modelMatrix);

	for (auto& model : *Model) {
		if (!model.vbo) {
			if (model.container.size() == 0)
				continue;
			if (!model.texturePath.empty())
				model.texture = new Texture(model.texturePath);
			model.vbo = tigl::createVbo(model.container);
			model.container.clear();
		}

		if (model.texture) {
			tigl::shader->enableTexture(true);
			model.texture->bind();
		}

		tigl::drawVertices(GL_TRIANGLES, model.vbo);

		Texture_unbind();
		tigl::shader->enableTexture(false);
	}
}
