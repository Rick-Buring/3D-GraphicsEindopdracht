#pragma once

#include <memory>
#include <vector>
#include <thread>

#include "GameObject.hpp"
#include "Player.hpp"
#include "ThirdPersonCamera.hpp"
#include "LoadScreen.hpp"
#include "LightManager.hpp"

enum STATE {
	RUNNING,
	LOADING,
	READY,
	ReloadPending
};

class Scene {
private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	std::shared_ptr<GameObject> _player;
	std::shared_ptr<ThirdPersonCamera> _camera;
	std::shared_ptr<LoadScreen> _loadScreen;
	std::thread _thread;
	lightStruct _sunLight;
	std::string _currentLevelPath;
	double _lastFrameTime;

	/// <summary>
	/// draws the new frame called after every update
	/// </summary>
	void draw();

	/// <summary>
	/// resets the scene. clears all the gameObjects and player
	/// </summary>
	void reset();

public:
	Scene();

	/// <summary>
	/// updates all gameObjects.
	/// </summary>
	void update();

	/// <summary>
	/// adds a single gameObject to the scene
	/// </summary>
	/// <param name="gameObject">gameObject to be added to the scene</param>
	void addGameObject(std::shared_ptr<GameObject> gameObject);

	/// <summary>
	/// adds a load of gameObjects to the scene
	/// </summary>
	/// <param name="gameObject">gameObjects to be added to the scene</param>
	void addGameObjects(std::vector<std::shared_ptr<GameObject>> gameObject);

	/// <summary>
	/// sets the scene up to change the scene next update cycle
	/// </summary>
	void loadLevel(const std::string& path);

	STATE state = RUNNING;
};