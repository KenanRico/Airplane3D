#include <glad/glad.h>

#include "mesh.h"

#include <vector>



Mesh::Mesh(unsigned int _vao, unsigned int _ebo, unsigned int ic, GLenum m, const std::vector<unsigned int>& tex):
ri((struct RenderInfo){_vao, _ebo, ic, m}), textures(tex){

}

Mesh::Mesh(unsigned int _vao, unsigned int _ebo, unsigned int ic, GLenum m):
ri((struct RenderInfo){_vao, _ebo, ic, m}){

}

Mesh::Mesh(const Mesh& rhs):
ri((struct RenderInfo){rhs.ri.VAO, rhs.ri.EBO, rhs.ri.indices_count, rhs.ri.mode}), textures(rhs.textures){

}

Mesh::~Mesh(){
}

const struct Mesh::RenderInfo& Mesh::getRI() const{
	return ri;
}
