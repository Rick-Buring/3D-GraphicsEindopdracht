#pragma once

#include <gl/glew.h>
#include <string>

class Texture
{
private:
	GLuint id;
public:
	Texture(const std::string& fileName);
	void bind();
};

/// <summary>
/// function to unbind textures in the tigle->shader
/// </summary>
void Texture_unbind();

