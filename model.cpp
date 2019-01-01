#include <glad/glad.h>

#include "model.h"
#include "mesh.h"
#include "gpubuffer.h"
#include "logger.h"

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Model::Model(const std::string& path){
	Assimp::Importer importer;
	aiScene const * scene = importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs);
	if(scene==nullptr || scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode==nullptr){
		Logger::toConsole(Logger::L_ERROR, std::string("Failed to load model for "+path));
	}else{
		loadModel(scene);
		Logger::toConsole(Logger::L_INFO, std::string("Loaded model for "+path));
	}
}

Model::Model(GPUbuffer const * buffers){
	//get render info surrounding one vao
	unsigned int vao = 0;
	unsigned int ebo = 0;
	unsigned int ic = 0;
	GLenum m;
	buffers->queryRenderInfo(&vao, &ebo, &ic, &m);
	//create mesh from vao
	meshes.push_back(Mesh(vao, ebo, ic, m));
}

Model::Model(const Model& rhs): meshes(rhs.meshes), model_texture_pool(rhs.model_texture_pool){

}

Model::~Model(){
	for(std::vector<unsigned int>::iterator t=model_texture_pool.begin(); t!=model_texture_pool.end(); ++t){
		glDeleteTextures(1, &(*t));
	}
}

void Model::loadModel(aiScene const * scene){

}

const std::vector<Mesh>& Model::getMeshes() const{
	return meshes;
}
