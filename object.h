#ifndef OBJECT_H
#define OBJECT_H
//-------------------------------------------------------------
#include <glad/glad.h>

#include "camera.h"
#include "gpubuffer.h"
#include "pipeline.h"
#include "model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Vehicle;
class Lighting;
class Shadow;

class Object{
	protected:
		struct RenderInfo{
			unsigned int VAO;
			unsigned int EBO;
			unsigned int indices_count;
			unsigned int instance_array_ID;
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
		//struct RenderInfo ri;
		Model const * model;
		unsigned int shader;
		struct GeometricProperties geometry;
		struct PhysicalProperties physics;
		struct Transformation transformation;
		bool exists;

	public:
		Object(Model const *, unsigned int, const glm::vec3&, float);
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
		virtual void sendInfoToShader(unsigned int) const;
		bool isAlive() const;
		const Model& getModel() const;
	protected:
		void syncProperties();

	friend void Pipeline::Renderer::renderEntities(std::vector<Object*> const *, Vehicle const *, std::vector<Lighting*> const *, const std::vector<Shadow*>&, const Camera&);
	friend void Pipeline::EnvironmentUpdater::updateShadow(std::vector<Shadow*>*, const std::vector<Object*>&, unsigned int);
};

//-------------------------------------------------------------
#endif
