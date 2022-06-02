#include "Player.hpp"
#include "Texture.hpp"

Player::Player(std::shared_ptr<std::vector<Model3D_t>> model) : GameObject(model)
{
}

void Player::update(float deltaTime)
{

}

void Player::draw()
{
	//todo replace camera
	GameObject::draw();

}
