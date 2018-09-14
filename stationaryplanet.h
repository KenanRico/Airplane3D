#ifndef STATIONARY_PLANET_H
#define STATIONARY_PLANET_H
//--------------------------------------------------------------

#include "nonplayableobject.h"
#include "camera.h"
#include "gpubuffer.h"

#include <glm/glm.hpp>


class StationaryPlanet : public NonPlayableObject{
	private: 
		struct Rotation{
			float speed;
			glm::vec3 orientation;
		};
	private:
		static float scale;
		struct Rotation rotation;
		/*inherited members:
			struct RenderInfo ri;
			unsigned int shader;
			struct Position position;
			Transformation transformation;
			glm::vec3 size;
		*/

	public:
		//StationaryPlanet(float*, unsigned int, unsigned int*, unsigned int, unsigned int, unsigned int, const glm::vec3&, float, float, const glm::vec3&);
		StationaryPlanet(GPUbuffer const *, unsigned int, const glm::vec3&, float, float, const glm::vec3&);
		virtual ~StationaryPlanet();
	private:
		StationaryPlanet() = delete;
		StationaryPlanet(const StationaryPlanet&) = delete;
		StationaryPlanet& operator=(const StationaryPlanet&) = delete;

	public:
		void update(const Camera&) override;
		void render() const override;
};

//--------------------------------------------------------------
#endif
