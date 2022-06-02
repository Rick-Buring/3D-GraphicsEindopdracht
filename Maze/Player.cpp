#include "Player.hpp"
#include "Texture.hpp"

Player::Player(std::shared_ptr<Model3D_t> model) : _model(model)
{
}

void Player::update(float deltaTime)
{

}

void Player::draw()
{
	GameObject::draw();

	_model->texture->bind();
	tigl::drawVertices(GL_TRIANGLES, _model->vbo);
}
