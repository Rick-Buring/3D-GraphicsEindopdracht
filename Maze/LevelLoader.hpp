#pragma once

#include "InteractableGameObject.hpp"
#include "Scene.hpp"

#include <memory>

class LevelLoader : public InteractableGameObject {
private:
	Scene* _scene;
	std::string _levelDataPath;

	LevelLoader(std::string levelDataPath, Scene* scene);

public:
	/// <summary>
	/// public static function that returns the levelLoader object if the levelDataPath points to a file
	/// </summary>
	/// <param name="levelDataPath"></param>
	/// <param name="scene">scene refrence</param>
	/// <returns></returns>
	static std::shared_ptr<LevelLoader> createLevelLoader(std::string levelDataPath, Scene* scene);

	// Inherited via InteractableGameObject
	virtual void interact(bool interacted) override;
};