#pragma once

#include "InteractableGameObject.hpp"
#include "Scene.hpp"

#include <memory>

class LevelLoader : public InteractableGameObject {
private:
	Scene* _scene;
	LevelLoader(std::string levelDataPath, Scene* scene);
public:
	std::string _levelDataPath;

	static std::shared_ptr<LevelLoader> createLevelLoader(std::string levelDataPath, Scene* scene);

	// Inherited via InteractableGameObject
	virtual void interact(bool interacted) override;
};