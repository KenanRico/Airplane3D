#include <glad/glad.h>

#include "model.h"
#include "mesh.h"
#include "gpubuffer.h"
#include "logger.h"

#include <string>
#include <vector>
#include <map>
#include <queue>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Model::Model(const std::string& path): model_dir(path.substr(0, path.find_last_of('/'))){
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

Model::Model(const Model& rhs): meshes(rhs.meshes), model_texture_pool(rhs.model_texture_pool), model_dir(rhs.model_dir){
	for(std::vector<unsigned int>::iterator vao=VAOs.begin(); vao!=VAOs.end(); ++vao){
		glDeleteVertexArrays(1, &(*vao));
	}
	for(std::vector<unsigned int>::iterator ebo=EBOs.begin(); ebo!=EBOs.end(); ++ebo){
		glDeleteBuffers(1, &(*ebo));
	}
}

Model::~Model(){
	for(std::map<std::string, unsigned int>::iterator t=model_texture_pool.begin(); t!=model_texture_pool.end(); ++t){
		glDeleteTextures(1, &(t->second));
	}
}

void Model::loadModel(aiScene const * scene){
	std::queue<aiNode*> queue({scene->mRootNode});
	while(!queue.empty()){
		//pop
		aiNode const * node = queue.front();
		queue.pop();
		//add node's meshes
		addNodeMeshes(scene, node);
		//add node's children to queue
		int children_count = node->mNumChildren;
		for(int i=0; i<children_count; ++i){
			queue.push(node->mChildren[i]);
		}
	}

}

const std::vector<Mesh>& Model::getMeshes() const{
	return meshes;
}

void Model::addNodeMeshes(aiScene const * scene, aiNode const * node){
	int mesh_count = node->mNumMeshes;
	for(int i=0; i<mesh_count; ++i){
		aiMesh const * mesh = scene->mMeshes[node->mMeshes[i]];
		int v_count = mesh->mNumVertices;
		//gen VAO: v, n, t
		std::vector<float> v; v.reserve(v_count*3);
		std::vector<float> n; n.reserve(v_count*3);
		std::vector<float> t; t.reserve(v_count*2);
		for(int j=0; j<v_count; ++j){
			v.push_back(mesh->mVertices[j].x); v.push_back(mesh->mVertices[j].y); v.push_back(mesh->mVertices[j].z);
			n.push_back(mesh->mNormals[j].x); n.push_back(mesh->mNormals[j].y); n.push_back(mesh->mNormals[j].z);
			if(mesh->HasTextureCoords(0)){
				t.push_back(mesh->mTextureCoords[0][j].x); t.push_back(mesh->mTextureCoords[0][j].y);
			}else{
				t.push_back(0.0); t.push_back(0.0);
			}
		}
		unsigned int VAO = GenVAO(v, n, t);
		VAOs.push_back(VAO);
		//gen EBO
		int face_count = mesh->mNumFaces;
		std::vector<unsigned int> indices;
		for(int j=0; j<face_count; ++j){
			const aiFace& face = mesh->mFaces[j];
			indices.insert(indices.end(), &(face.mIndices[0]), &(face.mIndices[face.mNumIndices]));
		}
		unsigned int EBO = GenEBO(indices);
		EBOs.push_back(EBO);
		unsigned int i_count = indices.size();
		//textures
		std::vector<unsigned int> textures;
		if(mesh->mMaterialIndex>=0){
			aiMaterial const * material = scene->mMaterials[mesh->mMaterialIndex];
			unsigned int diffuse_count = material->GetTextureCount(aiTextureType_DIFFUSE);
			for(unsigned int i=0; i<diffuse_count; ++i){
				aiString n("");
				material->GetTexture(aiTextureType_DIFFUSE, i, &n);
				std::string tex_name = n.C_Str();
				if(model_texture_pool.find(tex_name)==model_texture_pool.end()){
					std::string texture_path = model_dir+"/"+tex_name;
					//model_texture_pool
				}else{

				}
			}
			unsigned int specular_count = material->GetTextureCount(aiTextureType_SPECULAR);
			for(unsigned int i=0; i<specular_count; ++i){
				aiString n("");
			}
		}
		//add mesh
		meshes.push_back(Mesh(VAO, EBO, i_count, GL_TRIANGLES, textures));
	}
}

unsigned int Model::GenVAO(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& texcoords){
	//vao
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	//vbos
	unsigned int v_vbo = 0;
	glGenBuffers(1, &v_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &(vertices.at(0)), GL_STATIC_DRAW);
	unsigned int n_vbo = 0;
	glGenBuffers(1, &n_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), &(normals.at(0)), GL_STATIC_DRAW);
	unsigned int t_vbo = 0;
	glGenBuffers(1, &t_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
	glBufferData(GL_ARRAY_BUFFER, texcoords.size()*sizeof(float), &(texcoords.at(0)), GL_STATIC_DRAW);
	//bind vbos to vao
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	return VAO;
}

unsigned int Model::GenEBO(const std::vector<unsigned int>& indices){
	unsigned int EBO = 0;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices.at(0), GL_STATIC_DRAW);
	return EBO;
}
