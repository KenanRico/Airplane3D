#ifndef WEAPON_H
#define WEAPON_H
//------------------------------------------------------------------

#include "bullet.h"
#include "gpubuffer.h"
#include "camera.h"

#include <vector>
#include <string>


class Weapon{
	private:
		std::vector<Bullet*> bullets;
		unsigned int max_count;
		float max_distance;
		GPUbuffer const * gpu_buffer;
		std::string v_shader;
		std::string f_shader;
		float speed;
		float power;
		bool defined;

	public:
		Weapon(unsigned int, float);
		~Weapon();
	private:
		Weapon() = delete;
		Weapon(const Weapon&) = delete;
		Weapon& operator=(const Weapon&) = delete;

	public:
		void define(GPUbuffer const *, const std::string&, const std::string&, float, float);
		void attack(const glm::vec3&, const glm::vec3&, float);
		void updateBullets(const Camera&);
		void cleanUp(const glm::vec3&);
		void renderBullets() const;
};

//------------------------------------------------------------------
#endif
