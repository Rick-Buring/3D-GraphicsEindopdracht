#pragma once

#include "Scene.hpp"
#include "AbstractLevelDataReader.hpp"

typedef struct {
	glm::vec3 position;
	glm::vec3 rotation;
	unsigned char type;
} mazeValue;

#ifdef TEST

std::shared_ptr<std::vector<Model3D_t>> findModel(const std::string& name, std::vector<NamedModel3D_t>& list);

std::vector<mazeValue*> loadMazeFromImage(std::string imagePath);

std::vector<std::shared_ptr<GameObject>> generateGameObjects(Scene& scene, std::vector<LevelData_t>& leveldata, std::vector<NamedModel3D_t>& models, std::vector<mazeValue*>& maze);

#endif // TEST


void LoadNewScene(Scene& scene, std::string path);
void LoadNewSceneAsync(Scene* scene, std::string path);