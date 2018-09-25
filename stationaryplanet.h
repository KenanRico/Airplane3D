#ifndef STATIONARY_PLANET_H
#define STATIONARY_PLANET_H
//--------------------------------------------------------------

#include "object.h"
#include "camera.h"
#include "gpubuffer.h"

#include <glm/glm.hpp>


class StationaryPlanet : public Object{
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
			glm::vec3 velocity
			glm::vec3 size;
			Transformation transformation;
		*/

	public:
		StationaryPlanet(GPUbuffer const *, unsigned int, const glm::vec3&, float, float, const glm::vec3&);
		virtual ~StationaryPlanet();
	private:
		StationaryPlanet() = delete;
		StationaryPlanet(const StationaryPlanet&) = delete;
		StationaryPlanet& operator=(const StationaryPlanet&) = delete;

	public:
		void update(const Camera&) override;
		void render() const;
};

//--------------------------------------------------------------
#endif
