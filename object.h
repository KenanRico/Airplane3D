#ifndef OBJECT_H
#define OBJECT_H
//-------------------------------------------------------------
#include <glad/glad.h>

#include "camera.h"
#include "gpubuffer.h"
#include "physicshandler.h"

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
		struct GeometricProperties{
			struct Position position;
			struct Size size;
		};
		struct PhysicalProperties{
			float weight;
			float elasticity;
		};
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
	protected:
		struct RenderInfo ri;
		unsigned int shader;
		//struct Position position;
		//struct Size size;
		struct GeometricProperties geometry;
		struct PhysicalProperties physics;
		struct Transformation transformation;
		PhysicsHandler physics_handler;

	public:
		Object(GPUbuffer const *, unsigned int, const glm::vec3&, float);
		virtual ~Object();
	private:
		Object() = delete;
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	public:
		virtual void update(const Camera&);
		virtual void render() const;
	protected:
		virtual void computeTransformations(const Camera&);
		void applyTransformations();

	friend class PhysicsHandler;
};

//-------------------------------------------------------------
#endif
