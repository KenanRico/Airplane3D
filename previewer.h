#ifndef PREVIEWER_H
#define PREVIEWER_H
//----------------------------------------------------------------------------------

#include <map>
#include <string>

class Previewer{

	private:
		std::map<std::string, bool> settings;

	public:
		Previewer();
		~Previewer();
	private:
		Previewer(const Previewer&) = delete;
		Previewer& operator=(const Previewer&) = delete;

	public:
		void update();

};

//----------------------------------------------------------------------------------
#endif
