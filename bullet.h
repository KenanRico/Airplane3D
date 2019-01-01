#ifndef BULLET_H
#define BULLET_H
//---------------------------------------------------------------------

#include "object.h"
#include "gpubuffer.h"
#include "camera.h"

#include <string>

#include <glm/glm.hpp>

class Bullet: public Object{
	private:
		static std::string v_shader;
		static std::string f_shader;
		static unsigned shd;
		glm::vec3 direction;
		float speed;
		float power;
		Object* source;
	public:
		Bullet(const glm::vec3&/*pos*/, float/*size*/, const glm::vec3&/*direction*/, float/*speed*/, float/*power*/, Object* /*source*/);
		~Bullet();
	private:
		Bullet() = delete;
		Bullet(const Bullet&) = delete;
		Bullet& operator=(const Bullet&) = delete;

	public:
		void updateProperties() override;
		void computeTransformations(const Camera&) override;
};

//---------------------------------------------------------------------
#endif
