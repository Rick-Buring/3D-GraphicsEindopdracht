#include "Player.hpp"
#include "Texture.hpp"
#include "ObjectLoader.hpp"

Player::Player(std::vector<Model3D_t> model) : _model(model)
{
}

void Player::update(float deltaTime)
{

}

void Player::draw()
{
	GameObject::draw();

	for (auto model : _model) {
		model.texture->bind();
		tigl::drawVertices(GL_TRIANGLES, model.vbo);
	}
}
