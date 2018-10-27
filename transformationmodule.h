#ifndef TRANSFORMATION_MODULE_H
#define TRANSFORMATION_MODULE_H
//---------------------------------------------------------------------------------

#include "object.h"

#include <vector>


class TransformationModule{
	private:
		//some fields

	public:
		TransformationModule();
		~TransformationModule();
	private:
		TransformationModule(const TransformationModule&) = delete;
		TransformationModule& operator=(const TransformationModule&) = delete;

	public:
		void transformAll(std::vector<Object*>*) const;


};

//---------------------------------------------------------------------------------
#endif
