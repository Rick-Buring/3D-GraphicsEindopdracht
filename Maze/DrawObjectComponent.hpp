#pragma once
#include <vector>
#include "ObjectLoader.hpp"

class DrawObjectComponent {
public:
	DrawObjectComponent(std::vector<Model3D_t> object);

	void draw();
private:
	std::vector<Model3D_t> _object;

};
