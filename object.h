#ifndef OBJECT_H
#define OBJECT_H
//-------------------------------------------------------------
#include <glad/glad.h>

#include "camera.h"
#include "gpubuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Object{
	private:
		struct RenderInfo{
			unsigned int VBO;
			unsigned int VAO;
			unsigned int EBO;
			unsigned int indices_count;
			GLenum mode;
		};
		struct Position{
			glm::vec3 last;
			glm::vec3 current;
		};
		struct Size{
			glm::vec3 last;
			glm::vec3 current;
		};
		struct Transformation{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;			
		};
	protected:
		struct RenderInfo ri;
		unsigned int shader;
		struct Position position;
		struct Size size;
		Transformation transformation;

	public:
		//Object(float*, unsigned int, unsigned int*, unsigned int, unsigned int, unsigned int, const glm::vec3&, float);
		Object(GPUbuffer const *, unsigned int, const glm::vec3&, float);
		virtual ~Object();
	private:
		Object() = delete;
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	public:
		virtual void update(const Camera&) = 0;
		virtual void render() const = 0;
};

//-------------------------------------------------------------
#endif
