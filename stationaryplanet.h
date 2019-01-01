#ifndef STATIONARY_PLANET_H
#define STATIONARY_PLANET_H
//--------------------------------------------------------------

#include "object.h"
#include "camera.h"

#include <glm/glm.hpp>


class Model;
class StationaryPlanet : public Object{
	private:
		static float scale;
		float rotation_speed;
		/*inherited members:
			struct RenderInfo ri;
			unsigned int shader;
			struct Position position;
			glm::vec3 velocity
			glm::vec3 size;
			Transformation transformation;
		*/

	public:
		StationaryPlanet(Model const *, unsigned int, const glm::vec3&, float, float, const glm::vec3&);
		virtual ~StationaryPlanet();
	private:
		StationaryPlanet() = delete;
		StationaryPlanet(const StationaryPlanet&) = delete;
		StationaryPlanet& operator=(const StationaryPlanet&) = delete;

	public:
		void updateProperties() override;
		void computeTransformations(const Camera&) override;
};

//--------------------------------------------------------------
#endif
