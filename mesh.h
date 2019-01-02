#ifndef MESH_H
#define MESH_H
//-------------------------------------------------------------------

#include <glad/glad.h>

#include <vector>

class Mesh{
	public:
		struct RenderInfo{
			unsigned int VAO;
			unsigned int EBO;
			unsigned int indices_count;
			GLenum mode;
		};
	private:
		struct RenderInfo ri;
		std::vector<unsigned int> textures;

	public:
		Mesh(unsigned int, unsigned int, unsigned int, GLenum, const std::vector<unsigned int>&);
		Mesh(unsigned int, unsigned int, unsigned int, GLenum);
		Mesh(const Mesh&);
		~Mesh();
	private:
		Mesh() = delete;
		Mesh& operator=(const Mesh&) = delete;

	public:
		const struct RenderInfo& getRI() const;

};

//-------------------------------------------------------------------
#endif
