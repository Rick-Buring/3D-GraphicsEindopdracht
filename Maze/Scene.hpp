#pragma once

#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "Player.hpp"
#include "ThirdPersonCamera.hpp"
#include "LoadScreen.hpp"

class Scene {
private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	std::shared_ptr<Player> _player;
	std::shared_ptr<ThirdPersonCamera> _camera;
	std::shared_ptr<LoadScreen> _loadScreen;

	double _lastFrameTime;
	void draw();
	void reset();
	std::vector<std::vector<std::vector<std::shared_ptr<GameObject>>>> loadMazeFromImage(std::string, std::vector<NamedModel3D_t>& models,std::shared_ptr<std::vector<Model3D_t>>& cube);


public:
	Scene();
	void update();
	void addGameObject(std::shared_ptr<GameObject> gameObject);
	void loadLevel(const std::string& path);
};