#pragma once

#include "InteractableGameObject.hpp"
#include "Scene.hpp"

class LevelLoader : public InteractableGameObject {
private:
	std::string _levelDataPath;
	Scene* _scene;
	LevelLoader(std::string levelDataPath, Scene* scene);
public:
	static LevelLoader* createLevelLoader(std::string levelDataPath, Scene* scene);

	// Inherited via InteractableGameObject
	virtual void interact(bool interacted) override;
};