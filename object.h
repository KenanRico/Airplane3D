#ifndef OBJECT_H
#define OBJECT_H
//-------------------------------------------------------------
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object{
	private:
		struct RenderInfo{
			unsigned int VBO;
			unsigned int VAO;
			unsigned int EBO;
			unsigned int indices_count;
		};
		struct Position{
			glm::vec3 last;
			glm::vec3 current;
		};
		struct Transformation{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;			
		};
	private:
		struct RenderInfo ri;
		unsigned int shader;
		struct Position position;
		Transformation transformation;

	public:
		Object(float*, unsigned int, unsigned int*, unsigned int, unsigned int, unsigned int, const glm::vec3&);
		~Object();
	private:
		Object() = delete;
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	public:
		void update(const Camera&);
		void render() const;
};

//-------------------------------------------------------------
#endif
