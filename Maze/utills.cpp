#include "utills.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

std::shared_ptr<std::vector<Model3D_t>> buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color)
{
	std::shared_ptr<std::vector<Model3D_t>> returnValue = std::make_shared<std::vector<Model3D_t>>();
	std::vector<tigl::Vertex> verts;
	//bottom
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, -1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, -1, 0)));

	//top
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	//left
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(1, 0, 0)));

	//right
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(-1, 0, 0)));

	//back
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, -1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, -1)));

	//front
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));	
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	
	Model3D_t tempModel;
	tempModel.texture = nullptr;
	//tempModel.vbo = tigl::createVbo(verts);
	tempModel.vbo = nullptr;
	tempModel.container = verts;

	returnValue->push_back(tempModel);

	return returnValue;
}

std::shared_ptr<std::vector<Model3D_t>> buildSphere(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color)
{
	std::shared_ptr<std::vector<Model3D_t>> returnValue = std::make_shared<std::vector<Model3D_t>>();
	std::vector<tigl::Vertex> verts;

	int stacks = 64;
	int slices = 64;


	float thetaInc = (float)M_PI / stacks;
	float phiInc = (float)(2 * M_PI / slices);

	for (float theta = -(float)M_PI_2; theta < (float)M_PI_2; theta += thetaInc)
	{
		for (float phi = 0; phi < (float)(2 * M_PI); phi += phiInc)
		{
			glm::vec3 v1(glm::cos(theta) * glm::cos(phi), glm::cos(theta) * glm::sin(phi), glm::sin(theta));
			glm::vec3 v2(glm::cos(theta + thetaInc) * glm::cos(phi + phiInc), glm::cos(theta + thetaInc) * glm::sin(phi + phiInc), glm::sin(theta + thetaInc));
			glm::vec3 v3(glm::cos(theta + thetaInc) * glm::cos(phi), glm::cos(theta + thetaInc) * glm::sin(phi), glm::sin(theta + thetaInc));
			glm::vec3 v4(glm::cos(theta) * glm::cos(phi + phiInc), glm::cos(theta) * glm::sin(phi + phiInc), glm::sin(theta));

			verts.push_back(tigl::Vertex::PCN(p + v1 * s, color, v1));
			verts.push_back(tigl::Vertex::PCN(p + v3 * s, color, v3));
			verts.push_back(tigl::Vertex::PCN(p + v2 * s, color, v2));
			verts.push_back(tigl::Vertex::PCN(p + v1 * s, color, v1));
			verts.push_back(tigl::Vertex::PCN(p + v2 * s, color, v2));
			verts.push_back(tigl::Vertex::PCN(p + v4 * s, color, v4));
		}
	}



	Model3D_t tempModel;
	tempModel.texture = nullptr;
	//tempModel.vbo = tigl::createVbo(verts);
	tempModel.vbo = nullptr;
	tempModel.container = verts;

	returnValue->push_back(tempModel);

	return returnValue;
}

std::shared_ptr<std::vector<Model3D_t>> createPlane(float width, float height) {
	std::shared_ptr<std::vector<Model3D_t>> returnValue = std::make_shared<std::vector<Model3D_t>>();

	std::vector<tigl::Vertex> verts;

	glm::vec4 col = glm::vec4(1, 1, 1, 1);

	verts.push_back(tigl::Vertex::PCN(glm::vec3(-width, 0, -height), col, glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCN(glm::vec3(-width, 0, height), col, glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCN(glm::vec3(width, 0, -height), col, glm::vec3(0, 1, 0)));


	verts.push_back(tigl::Vertex::PCN(glm::vec3(width, 0, -height), col, glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCN(glm::vec3(width, 0, height), col, glm::vec3(0, 1, 0)));
	verts.push_back(tigl::Vertex::PCN(glm::vec3(-width, 0, height), col, glm::vec3(0, 1, 0)));


	Model3D_t tempModel;
	tempModel.texture = nullptr;
	//tempModel.vbo = tigl::createVbo(verts);
	tempModel.vbo = nullptr;
	tempModel.container = verts;

	returnValue->push_back(tempModel);

	return returnValue;
}