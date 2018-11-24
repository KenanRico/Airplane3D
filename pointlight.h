#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
//--------------------------------------------------------

#include "lighting.h"

#include <glm/glm.hpp>


class PointLight: public Lighting{

	public:
		struct AttenuationFactors{
			float k;
			float kl;
			float kq;
		};
	private:
		glm::vec3 const * position;
		AttenuationFactors attenuation;

	public:
		PointLight(float, const Color&, glm::vec3 const *, const AttenuationFactors&);
		~PointLight();
	private:
		PointLight() = delete;
		PointLight(const PointLight&) = delete;
		PointLight& operator=(const PointLight&) = delete;

	public:
		void update() override;
		void sendInfoToShader(unsigned int) const override;

};

//--------------------------------------------------------
#endif
