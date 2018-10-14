#ifndef REVOLVING_PLANET_H
#define REVOLVING_PLANET_H
//----------------------------------------------------------------
#include "object.h"
#include "camera.h"
#include "gpubuffer.h"

#include <glm/glm.hpp>


class RevolvingPlanet : public Object{
	private: 
		struct Revolution{
			float speed;
			glm::vec3 axis;
		};
	private:
		static float scale;
		struct Revolution revolution;
		/*inherited members:
			struct RenderInfo ri;
			unsigned int shader;
			struct Position position;
			Transformation transformation;
			glm::vec3 size;
		*/

	public:
		RevolvingPlanet(GPUbuffer const *, unsigned int, const glm::vec3&, float, float, const glm::vec3&);
		virtual ~RevolvingPlanet();
	private:
		RevolvingPlanet() = delete;
		RevolvingPlanet(const RevolvingPlanet&) = delete;
		RevolvingPlanet& operator=(const RevolvingPlanet&) = delete;

	public:
		void update(const Camera&) override;
		void render() const;
	private:
		void computeTransformations(const Camera&, struct Transformation*) override;
};

//----------------------------------------------------------------
#endif
