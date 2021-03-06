#include "LightManager.hpp"
#include <vector>
#include "tigl.h"

std::vector<lightInfo*> lightPointers = std::vector<lightInfo*>();

void addLight(lightInfo* out)
{
	out->lightId = (int)lightPointers.size();
	lightPointers.push_back(out);
	
	out->setLight();

	tigl::shader->setLightCount((int)lightPointers.size());
}

void removeLight(lightInfo* lightID)
{
	//remove the light
	lightPointers.erase(std::remove(lightPointers.begin(), lightPointers.end(), lightID));
	tigl::shader->setLightCount((int)lightPointers.size());

	for (int i = 0; i < lightPointers.size(); i++)
	{
		lightInfo* currentLight = lightPointers[i];
		currentLight->lightId = i;
		currentLight->setLight();
	}
}

void lightStruct::setLight()
{
	tigl::shader->setLightDirectional(lightId, isDirectional);
	tigl::shader->setLightPosition(lightId, position);
	tigl::shader->setLightAmbient(lightId, ambient);
	tigl::shader->setLightDiffuse(lightId, diffusion);
	tigl::shader->setLightSpecular(lightId, specular);
}
