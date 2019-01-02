#ifndef MODEL_H
#define MODEL_H
//--------------------------------------------------------------------

#include "mesh.h"
#include "gpubuffer.h"

#include <string>
#include <vector>
#include <map>

#include <assimp/scene.h>


class Model{
	private:
		std::vector<Mesh> meshes;
		std::map<std::string, unsigned int> model_texture_pool;
		std::string model_dir;
		std::vector<unsigned int> VAOs;
		std::vector<unsigned int> EBOs;

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
		void addNodeMeshes(aiScene const *, aiNode const *);
		unsigned int GenVAO(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);
		unsigned int GenEBO(const std::vector<unsigned int>&);
	public:
		const std::vector<Mesh>& getMeshes() const;

};

//--------------------------------------------------------------------
#endif
