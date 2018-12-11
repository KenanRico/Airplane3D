#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H
//----------------------------------------------------------------------------------

#include "lighting.h"

#include <glm/glm.hpp>


class DirectionalLight: public Lighting{
	private:
		glm::vec3 direction;

	public:
		DirectionalLight(float, const struct Color&, const glm::vec3&);
		~DirectionalLight();
	private:
		DirectionalLight(const DirectionalLight&) = delete;
		DirectionalLight& operator=(const DirectionalLight&) = delete;

	public:
		void update() override;
		void sendInfoToShader(unsigned int) const override;
		void calcLightSpaceMatrix(glm::mat4*) const override;
};

//----------------------------------------------------------------------------------
#endif
