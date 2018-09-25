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
		//render related
		struct RenderInfo ri;
		unsigned int shader;
		//movement related
		struct Position position;
		struct Size size;
		//trans
		Transformation transformation;

	public:
		Object(GPUbuffer const *, unsigned int, const glm::vec3&, float);
		virtual ~Object();
	private:
		Object() = delete;
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	public:
		virtual void update(const Camera&);
		void render() const;
	protected:
		void applyTransformations();
};

//-------------------------------------------------------------
#endif
