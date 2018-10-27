#ifndef HANDLER_MODULE_H
#define HANDLER_MODULE_H

//------------------------------------------------------------------------------------

#include "object.h"

#include <vector>


class HandlerModule{

	private:
		//some fields

	public:
		//constructors
		HandlerModule();
		~HandlerModule();
	private:
		HandlerModule(const HandlerModule&) = delete;
		HandlerModule& operator=(const HandlerModule&) = delete;

	public:
		void handlePhysics(std::vector<Object*>*) const;
		void handleControls(std::vector<Object*>* ,std::vector<Object*>*) const;
		void handleGeometry(std::vector<Object*>*) const;

};

//------------------------------------------------------------------------------------
#endif
