#pragma once

#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "Player.hpp"
#include "ThirdPersonCamera.hpp"

class Scene {
private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	std::shared_ptr<Player> _player;
	std::shared_ptr<ThirdPersonCamera> _camera;

	double _lastFrameTime;
	void draw();
	void reset();
	void loadMazeFromFile(std::string, std::shared_ptr<std::vector<Model3D_t>>& cube);


public:
	Scene();
	void update();
	void addGameObject(std::shared_ptr<GameObject> gameObject);
	void loadLevel(const std::string& path);
};