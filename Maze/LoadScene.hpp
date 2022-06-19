#pragma once

#include "Scene.hpp"

void LoadNewScene(Scene& scene, std::string path);
void LoadNewSceneAsync(Scene* scene, std::string path);