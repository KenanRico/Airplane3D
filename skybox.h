#ifndef SKYBOX_H
#define SKYBOX_H
//-------------------------------------------------------------------

#include <glad/glad.h>

#include "gpubuffer.h"
#include "pipeline.h"

#include <glm/glm.hpp>

class Skybox{
	private:
		struct ModelTransformation{
			glm::mat4 scale;
			glm::mat4 rotate;
			glm::mat4 translate;
			glm::mat4 overall;
		};
		struct Transformation{
			struct ModelTransformation model;
			glm::mat4 view;
			glm::mat4 projection;
		};
	private:
		struct RenderInfo{
			unsigned int VAO;
			unsigned int EBO;
			unsigned int indices_count;
			GLenum mode;
		};
	private:
		RenderInfo ri;
		unsigned int texture_ID;
		unsigned int shader;
		struct Transformation transformation;

	public:
		Skybox();
		~Skybox();
	private:
		Skybox(const Skybox&) = delete;
		Skybox& operator=(const Skybox&) = delete;

	public:
		void initialize(GPUbuffer const *, unsigned int);
		void computeTransformations(const Camera&);

	friend void Pipeline::Renderer::renderEnvironment(const Skybox&);
};

//-------------------------------------------------------------------
#endif
