#include "weapon.h"
#include "bullet.h"
#include "gpubuffer.h"
#include "shader.h"
#include "logger.h"
#include "camera.h"


#include <vector>
#include <string>

#include <glm/glm.hpp>


#define VERSION 1


Weapon::Weapon(unsigned int mc, float md): max_count(mc), max_distance(md){
	//nothin
}

Weapon::~Weapon(){
	for(std::vector<Bullet*>::iterator b=bullets.begin(); b!=bullets.end(); ++b){
		delete *b;
	}
}


void Weapon::define(GPUbuffer const * gb, const std::string& v, const std::string& f, float spd, float pow){
	if(!defined){
		gpu_buffer = gb;
		v_shader = v;
		f_shader = f;
		speed = spd;
		power = pow;
		defined = true;
	}else{
		Logger::toConsole(Logger::L_ERROR, "This weapon is already defined!");
	}
}

void Weapon::attack(const glm::vec3& pos, const glm::vec3& dir, float base_spd){
	if(bullets.size()<max_count){
		bullets.push_back(new Bullet(gpu_buffer, Shader::initShaders(v_shader, f_shader), pos, 1.0f, dir, base_spd+speed, power));
	}
}

void Weapon::updateBullets(const Camera& camera){
	for(std::vector<Bullet*>::iterator b=bullets.begin(); b!=bullets.end(); ++b){
		(*b)->update(camera);
	}
}

void Weapon::renderBullets() const{
	for(std::vector<Bullet*>::const_iterator b=bullets.begin(); b!=bullets.end(); ++b){
		(*b)->render();
		//Logger::toConsole(Logger::L_ERROR, "This weapon is already defined!");
	}
}

void Weapon::cleanUp(const glm::vec3& weapon_pos){
	for(std::vector<Bullet*>::iterator b=bullets.begin(); b!=bullets.end(); ++b){
		if(glm::length((*b)->geometry.position.current-weapon_pos) > max_distance){
			delete *b;
			bullets.erase(b--);
		}
	}
}
