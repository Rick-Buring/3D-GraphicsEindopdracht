#include "LoadScene.hpp"
#include "AbstractLevelDataReader.hpp"
#include "stb_image.h"
#include <iostream>

#include "Sun.hpp"
#include "utills.hpp"
#include "InteractableGameObject.hpp"
#include "MovingWall.hpp"
#include "Button.hpp"
#include "LevelLoader.hpp"

typedef struct {
	glm::vec3 position;
	glm::vec3 rotation;
	unsigned char type;
} mazeValue;

static std::vector<LevelData_t> getLevelData(std::string path) {
	AbstractLevelDataReader* reader = getReader(path);
	return reader->readData(path);
}

static LevelData_t popfront(std::vector<LevelData_t>& data) {
	LevelData_t value = data.at(0);
	data.erase(data.begin());
	return value;
}

static std::shared_ptr<std::vector<Model3D_t>> findModel(const std::string& name, std::vector<NamedModel3D_t>& list) {
	for (auto& obj : list) {
		if (obj.modelName == name) {
			return obj.model;
		}
	}
	return nullptr;
}


static std::vector<mazeValue*> loadMazeFromImage(std::string imagePath, unsigned char modelCount) {
	int width, height, bpp;
	unsigned char* image = stbi_load(imagePath.c_str(), &width, &height, &bpp, 4);
	//check if maze loaded succefully
	if (!image) {
		std::cout << "invalid maze path" << std::endl << imagePath << std::endl;
		return std::vector<mazeValue*>();
	}

	auto maze = std::vector<mazeValue*>(width * height * 3);


	int index = 0;
	for (size_t z = 0; z < height; z++)
	{
		for (int x4 = 0; x4 < width * 4; x4 += 4)
		{
			int x = x4 / 4;

			//objects position is x y z
			//x is encoded in width of image
			//z is encoded in height of image
			//y is encoded in color channel of image
			//value in chanel is the index of the object to render
			unsigned char rgb[] = {
				image[z * height * 4 + x4 + 0],
				image[z * height * 4 + x4 + 1],
				image[z * height * 4 + x4 + 2]
			};

			//encoded value used for rotation 
			//         y2 y1 y0 **
			// example 11 10 01 11 = 270 degrees on y 2, 180 degrees on y 1, 90 degrees on y 0
			// example y0 270 y1 0 degrees y2 180 degrees = 10 00 11 11
			unsigned char a = image[z * height * 4 + x + 3];

			for (size_t y = 0; y < 3; y++) {
				if (rgb[y]) {
					char rotation = (a >> (y + 1)) & 0x3;

					maze[index] = new mazeValue{
						glm::vec3(x, y, z), //position
						glm::vec3(0, glm::radians(90.0f * rotation), 0), //rotation
						rgb[y] //type
					};

					index++;
				}
			}
		}
	}
	maze.erase(std::remove(maze.begin(), maze.end(), nullptr), maze.end());

	return maze;
}

static std::vector<std::shared_ptr<GameObject>> generateGameObjects(Scene& scene, std::vector<LevelData_t>& leveldata, std::vector<NamedModel3D_t>& models, std::vector<mazeValue*>& maze) {
	//standart objects
	std::shared_ptr<std::vector<Model3D_t>> cube = buildCube(glm::vec3(0), glm::vec3(0.5), glm::vec4(1));
	std::shared_ptr<std::vector<Model3D_t>> sphere = buildSphere(glm::vec3(0), glm::vec3(0.5), glm::vec4(1));

	//return value
	std::vector<std::shared_ptr<GameObject>> returnValue = std::vector <std::shared_ptr<GameObject>>();
	//create player at start of return value
	std::shared_ptr<Player> player = nullptr;

	returnValue.push_back(player);

	for (auto& structData : leveldata)
	{
		levelData_st data = structData.data;
		std::string dataType = data.type;

		if (dataType == "player") {
			//only one player per level
			if (player)
				continue;

			player = std::make_shared<Player>(findModel("player", models));
			player->scale = glm::vec3(0.1f);
			player->position = data.position;
			player->position.y -= 0.5f;

			returnValue[0] = player;
		}
		else if (dataType == "sun")
		{
			//create sun
			auto sun = std::make_shared<Sun>(sphere);
			sun->scale = glm::vec3(5.0f);
			returnValue.push_back(sun);
		}
		else if (dataType == "butten") {
			mazeValue const* valueToRemove = nullptr;
			for (const auto& mazeV : maze) {
				if (mazeV->position == data.Linkedposition) {
					valueToRemove = mazeV;
					std::shared_ptr<std::vector<Model3D_t>> model = 
						mazeV->type == 255 ? cube : 
						mazeV->type < models.size() ? models[mazeV->type].model :
						models[mazeV->type % models.size()].model;

					std::shared_ptr<InteractableGameObject> interactingObject =
						std::string(data.linkedWithType) == "moving_wall" ? std::make_shared<MovingWall>(model, mazeV->position, data.action) :
						nullptr;
					interactingObject->rotation = mazeV->rotation;
					returnValue.push_back(interactingObject);

					auto butten = std::make_shared<Button>(cube, player.get(), data.position, interactingObject.get());
					butten->scale = glm::vec3(.5f);

					returnValue.push_back(butten);

					break;
				}
			}
			if (valueToRemove) {
				maze.erase(std::remove(maze.begin(), maze.end(), valueToRemove), maze.end());
			}
		}
		else if (dataType == "level") {
			std::shared_ptr<LevelLoader> levelLoader = LevelLoader::createLevelLoader(data.linkedWithType, &scene);
			if (levelLoader) {
				returnValue.push_back(levelLoader);

				auto butten = std::make_shared<Button>(cube, player.get(), data.position, levelLoader.get());
				butten->scale = glm::vec3(.5f);
				returnValue.push_back(butten);
			}
		}
	}

	for (const auto& mazeV: maze) {
		std::shared_ptr<std::vector<Model3D_t>> model =
			mazeV->type == 255 ? cube :
			mazeV->type < models.size() ? models[mazeV->type].model :
			models[mazeV->type % models.size()].model;
		std::shared_ptr<GameObject> go = std::make_shared<GameObject>(model);
		go->position = mazeV->position;
		go->rotation = mazeV->rotation;
		returnValue.push_back(go);

	}

	return returnValue;
}

void LoadNewScene(Scene& scene, std::string path)
{
	//rad level file
	auto levelData = getLevelData(path);

	//load 3d models
	auto models = loadObjects(popfront(levelData).path);

	//load maze
	auto maze = loadMazeFromImage(popfront(levelData).path, models.size());

	//generate gameObjects
	auto gameObjects = generateGameObjects(scene, levelData, models, maze);

	//add gameObjects to scene
	scene.addGameObjects(gameObjects);
}

void LoadNewSceneAsync(Scene* scene, std::string path)
{
	LoadNewScene(*scene, path);
	scene->stopLoading();
}

void LoadNewSceneAsync()
{
}
