#ifndef SHADOW_H
#define SHADOW_H
//---------------------------------------------------------------

#include "lighting.h"

#include <vector>

#include <glm/glm.hpp>

class Shadow{ //a shadow is the shadow system from a single light source
	public:
		static const unsigned int shadow_width;
		static const unsigned int shadow_height;
	private:
		unsigned int depth_map_FBO;
		unsigned int depth_map;
		Lighting const * source;
		glm::mat4 light_space_mat;

	public:
		Shadow(Lighting const *);
		~Shadow();
	private:
		Shadow() = delete;
		Shadow(const Shadow&) = delete;
		Shadow& operator=(const Shadow&) = delete;

	public:
		void updateLightSpaceMat();
		void sendInfoToShader() const;
		unsigned int getDepthMapFBO() const;
		const glm::mat4& getLSM() const;
		unsigned int getDepthMapTexture() const;
};

//---------------------------------------------------------------
#endif
