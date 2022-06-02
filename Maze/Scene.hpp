#pragma once

#include <memory>
#include <vector>
#include "GameObject.hpp"

class Scene {
private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	double _lastFrameTime;
	void draw();

public:
	void update();
	void addGameObject(std::shared_ptr<GameObject> gameObject);
	void initBaseScene();

};