#include "ObjectLoader.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <filesystem>
#include "tigl.h"

#include "Texture.hpp"
#include "stringUtil.hpp"
namespace fs = std::filesystem;
const std::string objectFileExtension = ".obj";

/**
* Replaces a substring in a string
*/
static std::string replace(std::string str, const std::string& toReplace, const std::string& replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

/**
* Splits a string into substrings, based on a seperator
*/
static std::vector<std::string> split(std::string str, const std::string& seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

/**
* Turns a string to lowercase
*/
static inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

/**
* Cleans up a line for processing
*/
static inline std::string cleanLine(std::string line)
{
	line = replace(line, "\t", " ");
	while (line.find("  ") != std::string::npos)
		line = replace(line, "  ", " ");
	if (line == "")
		return "";
	if (line[0] == ' ')
		line = line.substr(1);
	if (line == "")
		return "";
	if (line[line.length() - 1] == ' ')
		line = line.substr(0, line.length() - 1);
	return line;
}
void loadMaterialFile(const std::string& fileName, const std::string& dirName);

struct Vertex {
	int position;
	int normal = -1;
	int texcoord = -1;
};
struct Face
{
	std::list<Vertex> vertices;
};
struct ObjGroup
{
public:
	std::string name;
	int materialIndex;
	std::list<Face> faces;
};
struct MaterialInfo {
public:
	std::string name;
	std::string Path;
	Texture* texture;
};

std::vector<glm::vec3>	vertices;
std::vector<glm::vec3>	normals;
std::vector<glm::vec2>	texcoords;
std::vector<ObjGroup*> groups;
std::vector<MaterialInfo*> materials;

std::shared_ptr<std::vector<Model3D_t>> generateVBO(std::shared_ptr<std::vector<Model3D_t>>& returnValue)
{
	//foreach group in groups
	//  set material texture, if available
	//  set material color, if available
	//  foreach face in group
	//    foreach vertex in face
	//      emit vertex
	for (auto& g : groups)
	{

		//Texture* t = g->materialIndex > -1 ? materials[g->materialIndex]->texture : nullptr;
		std::string texturePath = g->materialIndex > -1 ? materials[g->materialIndex]->Path : "";
		std::vector<tigl::Vertex> container;

		for (auto &f : g->faces) {

			for (auto &v : f.vertices) {
				if (v.normal > -1 && v.texcoord > -1) {
					container.push_back(tigl::Vertex::PTN(vertices[v.position], texcoords[v.texcoord], normals[v.normal]));
				}
				else if (v.texcoord > 0) {
					container.push_back(tigl::Vertex::PT(vertices[v.position], texcoords[v.texcoord]));
				}
				else if (v.normal > 0) {
					container.push_back(tigl::Vertex::PN(vertices[v.position], normals[v.normal]));
				}
				else {
					container.push_back(tigl::Vertex::P(vertices[v.position]));
				}
			}

		}

		//tigl::VBO* vbo = tigl::createVbo(container);
		Model3D_t temp = Model3D_t();
		temp.texture = nullptr;
		temp.vbo = nullptr;
		temp.container = container;
		temp.texturePath = texturePath;
		returnValue->push_back(temp);

	}
	return returnValue;
}

//recursive function to read all files in folder and if the file is a .obj file load the object
void ObjectLoader_loadObjects(const std::string& path, std::vector<NamedModel3D_t>& objectsFromFile) {
	if (fs::is_directory(path)) {
		for (const auto& entry : fs::directory_iterator(path)) {
			fs::path path = entry.path();
			ObjectLoader_loadObjects(path.u8string(), objectsFromFile);
		}
	}
	else if (stringEndsWith(path, objectFileExtension)) {
		std::shared_ptr<std::vector<Model3D_t>> obj = ObjectLoader_loadObject(path);
		std::string fileName = ((fs::path)path).filename().u8string();
		fileName = fileName.substr(0, fileName.size() - objectFileExtension.size());
		NamedModel3D_t namedModel{ fileName, obj };
		objectsFromFile.push_back(namedModel);
	}
}

static void stringtoLowerCase(std::string& out) {
	std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) { return std::tolower(c); });
}
static bool compareByName(const NamedModel3D_t& a, const NamedModel3D_t& b)
{
	std::string lowerA = a.modelName.c_str(), lowerB = b.modelName.c_str();
	stringtoLowerCase(lowerA);
	stringtoLowerCase(lowerB);
	int value = lowerA.compare(lowerB);
	return value < 0;
}

std::vector<NamedModel3D_t> ObjectLoader_loadObjects(const std::string& fileName) {
	auto returnValue = std::vector<NamedModel3D_t>();
	ObjectLoader_loadObjects(fileName.c_str(), returnValue);
	std::sort(returnValue.begin(), returnValue.end(), compareByName);
	return returnValue;
}

/**
* Loads an object model
*/
std::shared_ptr<std::vector<Model3D_t>> ObjectLoader_loadObject(const std::string& fileName)
{
	vertices = std::vector<glm::vec3>();
	normals = std::vector<glm::vec3>();
	texcoords = std::vector<glm::vec2>();
	groups = std::vector<ObjGroup*>();
	materials = std::vector<MaterialInfo*>();

	std::shared_ptr<std::vector<Model3D_t>> returnValue = std::make_shared<std::vector<Model3D_t>>();

	std::cout << "Loading " << fileName << std::endl;
	std::string dirName = ((fs::path)fileName).remove_filename().u8string();

	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;

		return returnValue;
	}


	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#') //skip empty or commented line
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
			vertices.push_back(glm::vec3((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vn")
			normals.push_back(glm::vec3((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(glm::vec2((float)atof(params[1].c_str()), 1 - (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)	//magische forlus om van quads triangles te maken ;)
				{
					Vertex vertex = Vertex();
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)	//er is een positie
						vertex.position = atoi(indices[0].c_str()) - 1;
					if (indices.size() == 2)		//alleen texture
						vertex.texcoord = atoi(indices[1].c_str()) - 1;
					if (indices.size() == 3)		//v/t/n of v//n
					{
						if (indices[1] != "")
							vertex.texcoord = atoi(indices[1].c_str()) - 1;
						vertex.normal = atoi(indices[2].c_str()) - 1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if (params[0] == "s")
		{//smoothing groups
		}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = (int)i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1)
				std::cout << "Could not find material name " << params[1] << std::endl;
		}
	}
	groups.push_back(currentGroup);

	return generateVBO(returnValue);
}

void loadMaterialFile(const std::string& fileName, const std::string& dirName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::ifstream pFile(fileName.c_str());
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			std::string tex = params[1];
			if (tex.find("/"))
				tex = tex.substr(tex.rfind("/") + 1);
			if (tex.find("\\"))
				tex = tex.substr(tex.rfind("\\") + 1);
			//TODO
			//currentMaterial->texture = new Texture(dirName + "/" + tex);
			currentMaterial->Path = dirName + "/" + tex;
		}
		else if (params[0] == "kd")
		{//TODO, diffuse color
		}
		else if (params[0] == "ka")
		{//TODO, ambient color
		}
		else if (params[0] == "ks")
		{//TODO, specular color
		}
		else if (
			params[0] == "illum" ||
			params[0] == "map_bump" ||
			params[0] == "map_ke" ||
			params[0] == "map_ka" ||
			params[0] == "map_d" ||
			params[0] == "d" ||
			params[0] == "ke" ||
			params[0] == "ns" ||
			params[0] == "ni" ||
			params[0] == "td" ||
			params[0] == "tf" ||
			params[0] == "tr" ||
			false)
		{
			//these values are usually not used for rendering at this time, so ignore them
		}
		else
			std::cout << "Didn't parse " << params[0] << " in material file" << std::endl;
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}
