#ifndef OBJECT_H
#define OBJECT_H
//-------------------------------------------------------------
#include <glad/glad.h>

#include "camera.h"
#include "gpubuffer.h"
#include "pipeline.h"
#include "lighting.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Object{
	protected:
		struct RenderInfo{
			unsigned int VAO;
			unsigned int EBO;
			unsigned int indices_count;
			GLenum mode;
		};
		struct Position{
			glm::vec3 last;
			glm::vec3 current;
		};
		struct Rotation{
			glm::vec3 orientation;
			float last;
			float current;
		};
		struct Size{
			glm::vec3 last;
			glm::vec3 current;
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
	public:
		struct GeometricProperties{
			struct Position position;
			struct Rotation rotation;
			struct Size size;
		};
		struct PhysicalProperties{
			float weight;
			float elasticity;
			glm::vec3 velocity;
		};

	protected:
		struct RenderInfo ri;
		unsigned int shader;
		//struct Position position;
		//struct Size size;
		struct GeometricProperties geometry;
		struct PhysicalProperties physics;
		struct Transformation transformation;
		bool exists;

	public:
		Object(GPUbuffer const *, unsigned int, const glm::vec3&, float);
		virtual ~Object();
	private:
		Object() = delete;
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	public:
		struct GeometricProperties* getGeometry();
		struct PhysicalProperties* getPhysics();
		virtual void updateProperties();
		virtual void control(std::vector<Object*>*);
		virtual void computeTransformations(const Camera&);
		bool isAlive() const;
	protected:
		void syncProperties();

	friend void Pipeline::Renderer::renderEntities(std::vector<Object*> const *, std::vector<Lighting*> const *, const Camera&);
};

//-------------------------------------------------------------
#endif
