#include "LevelLoader.hpp"

#include <filesystem>
#include <iostream>
#include "Scene.hpp"

namespace fs = std::filesystem;

LevelLoader::LevelLoader(std::string levelDataPath, Scene* scene) : InteractableGameObject(nullptr), _levelDataPath(levelDataPath), _scene(scene)
{
}

std::shared_ptr<LevelLoader> LevelLoader::createLevelLoader(std::string levelDataPath, Scene* scene)
{
	if (fs::exists(levelDataPath)) {
		return std::make_shared<LevelLoader>(LevelLoader(levelDataPath, scene));
	}
	
	std::cout << "invalid level path " << levelDataPath << std::endl;

	return nullptr;
}

void LevelLoader::interact(bool interacted)
{
	_scene->loadLevel(_levelDataPath);
}
