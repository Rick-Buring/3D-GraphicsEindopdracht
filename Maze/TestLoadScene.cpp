#ifdef TEST

#include "catch.hpp"
#include "LoadScene.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::shared_ptr<std::vector<Model3D_t>> model1 = std::make_shared<std::vector<Model3D_t>>(), model2 = std::make_shared<std::vector<Model3D_t>>();

std::vector<NamedModel3D_t> list = {
	NamedModel3D_t{
		"model1",
		model1,
		},
		NamedModel3D_t{
		"model2",
		model2,
		}
};

TEST_CASE("Find model when modelname is not present in list") {
	auto result = findModel("Steve", list);
	REQUIRE(result == nullptr);
}


TEST_CASE("Find model when modelname is present in list and returns correct value") {
	auto result = findModel("model1", list);
	REQUIRE(result == model1);
	result = findModel("model2", list);
	REQUIRE(result == model2);
}


TEST_CASE("Load maze throws error when file does not exist") {
	REQUIRE_THROWS(loadMazeFromImage(""));
}

TEST_CASE("Load maze with correct size") {
	const int w = 2, h = 2, channelCount = 4;
	unsigned char data[w * h * channelCount] = {
		0xff,0xff,0xff,0xff,	0xff,0xff,0xff,0xff,		
		0xff,0xff,0xff,0xff,	0xff,0xff,0xff,0xff,
	};
	stbi_write_png("jpg_test_.png", w, h, channelCount, data, w * sizeof(unsigned char));
	auto maze = loadMazeFromImage("jpg_test_.png");

	REQUIRE(maze.size() == 2 * 2 * 3);
}

TEST_CASE("GameObject generate correct") {

}

#endif // TEST
