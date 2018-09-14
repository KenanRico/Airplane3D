#ifndef NON_PLAYABLE_OBJECT_H
#define NON_PLAYABLE_OBJECT_H
//-----------------------------------------------------------------------

#include "object.h"
#include "camera.h"
#include "gpubuffer.h"

#include <glm/glm.hpp>


class NonPlayableObject: public Object{
	/*inherited members:
		struct RenderInfo ri;
		unsigned int shader;
		struct Position position;
		Transformation transformation;
		glm::vec3 size;
	*/
	public:
		//NonPlayableObject(float*, unsigned int, unsigned int*, unsigned int, unsigned int, unsigned int, const glm::vec3&, float);
		NonPlayableObject(GPUbuffer const *, unsigned int, const glm::vec3&, float);
		virtual ~NonPlayableObject();
	private:
		NonPlayableObject() = delete;
		NonPlayableObject(const NonPlayableObject&) = delete;
		NonPlayableObject& operator=(const NonPlayableObject&) = delete;

	public:
		virtual void update(const Camera&) override = 0;
		virtual void render() const override = 0;
};

//-----------------------------------------------------------------------
#endif
