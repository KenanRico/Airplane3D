#ifndef PIPELINE_H
#define PIPELINE_H
//------------------------------------------------------------------------

#include <vector>

class Object;
namespace Pipeline{

	namespace Updater{

	};

	namespace Renderer{
		void renderEntities(std::vector<Object*> const *);
	}

};

//---------------------------------------------------------------------
#endif
