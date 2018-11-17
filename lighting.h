#ifndef LIGHTING_H
#define LIGHTING_H
//----------------------------------------------------------------------------

#include <glm/glm.hpp>

class Lighting{
	public:
		struct Color{
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};
	protected:
		float intensity;
		struct Color color;

	public:
		Lighting(float, const struct Color&);
		virtual ~Lighting();
	private:
		Lighting() = delete;
		Lighting(const Lighting&) = delete;
		Lighting& operator=(const Lighting&) = delete;

	public:
		virtual void update() = 0;
		virtual void sendInfoToShader(unsigned int) = 0;
};

//----------------------------------------------------------------------------
#endif
