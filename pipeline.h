#ifndef PIPELINE_H
#define PIPELINE_H
//------------------------------------------------------------------------

#include "camera.h"
#include "lighting.h"
#include "shadow.h"

#include <vector>

class Object;
class Vehicle;

namespace Pipeline{

	namespace Updater{
		void handleControls(std::vector<Object*>*, std::vector<Object*>*);
		void handlePhysics(std::vector<Object*>*);
		void handlePropertyUpdate(std::vector<Object*>*);
	};

	namespace Transformer{
		void transformAll(std::vector<Object*>*, const Camera&);
	};

	namespace Renderer{
		void renderEntities(std::vector<Object*> const *, Vehicle const *, std::vector<Lighting*> const *, const std::vector<Shadow*>&, const Camera&);
	};

	namespace EnvironmentUpdater{
		void handleLighting(std::vector<Lighting*>*);
		void updateShadow(std::vector<Shadow*>*, const std::vector<Object*>&, unsigned int);
	};

};

//---------------------------------------------------------------------
#endif
