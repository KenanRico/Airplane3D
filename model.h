#ifndef MODEL_H
#define MODEL_H
//--------------------------------------------------------------------

#include "mesh.h"
#include "gpubuffer.h"

#include <string>
#include <vector>

#include <assimp/scene.h>


class Model{
	private:
		std::vector<Mesh> meshes;
		std::vector<unsigned int> model_texture_pool;

	public:
		Model(const std::string&); //load from model file
		Model(GPUbuffer const *); //load from simple-shape gpubuffer (one mesh, one VAO)
		Model(const Model&);
		~Model();
	private:
		Model() = delete;
		Model& operator=(const Model&) = delete;

	private:
		void loadModel(aiScene const *);
	public:
		const std::vector<Mesh>& getMeshes() const;

};

//--------------------------------------------------------------------
#endif
