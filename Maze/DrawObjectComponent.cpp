#include "DrawObjectComponent.hpp"
#include "Texture.hpp"

DrawObjectComponent::DrawObjectComponent(std::vector<Model3D_t> object) :_object(object)
{

}
void DrawObjectComponent::draw()
{
	for (auto d : _object) {
		d.texture->bind();
		tigl::drawVertices(GL_TRIANGLES, d.vbo);
	}
}
