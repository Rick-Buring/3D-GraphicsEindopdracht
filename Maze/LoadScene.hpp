#pragma once

#include "Scene.hpp"
#include "AbstractLevelDataReader.hpp"

typedef struct {
	glm::vec3 position;
	glm::vec3 rotation;
	unsigned char type;
} mazeValue;

//private functions exposed in testing circumstances
#ifdef TEST

std::shared_ptr<std::vector<Model3D_t>> findModel(const std::string& name, std::vector<NamedModel3D_t>& list);

std::vector<mazeValue*> loadMazeFromImage(std::string imagePath);

std::vector<std::shared_ptr<GameObject>> generateGameObjects(Scene& scene, std::vector<LevelData_t>& leveldata, std::vector<NamedModel3D_t>& models, std::vector<mazeValue*>& maze);

#endif // TEST

/// <summary>
/// loads a new scene
/// </summary>
/// <param name="scene">Scene to be loaded</param>
/// <param name="path">Path to the levelFile</param>
void LoadNewScene(Scene& scene, std::string path);

/// <summary>
/// loads a new scene, Warning this should be called from a diffrent thread then main.
/// no problems if called from main other then efficiency sake
/// </summary>
void LoadNewSceneAsync(Scene* scene, std::string path);
