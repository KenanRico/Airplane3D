#ifndef BULLET_H
#define BULLET_H
//---------------------------------------------------------------------

#include "object.h"
#include "gpubuffer.h"
#include "camera.h"

#include <glm/glm.hpp>


class Bullet: public Object{
	private:
		glm::vec3 direction;
		float speed;
		float power;
	public:
		Bullet(GPUbuffer const *, unsigned int, const glm::vec3&, float, const glm::vec3&/*direction*/, float/*speed*/, float/*power*/);
		~Bullet();
	private:
		Bullet() = delete;
		Bullet(const Bullet&) = delete;
		Bullet& operator=(const Bullet&) = delete;

	public:
		void update(const Camera&) override;
		void computeTransformations(const Camera&, struct Transformation*) override;

	friend class Weapon;
};

//---------------------------------------------------------------------
#endif
