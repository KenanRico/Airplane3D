#ifndef PREVIEWER_H
#define PREVIEWER_H
//----------------------------------------------------------------------------------

class Previewer{

	private:
		enum class GammaMode {NONE, DEFAULT, CUSTOM};

	private:
		GammaMode gamma;

	public:
		Previewer();
		~Previewer();
	private:
		Previewer(const Previewer&) = delete;
		Previewer& operator=(const Previewer&) = delete;

	public:
		void update();
		void enableShaderGamma(bool) const;

};

//----------------------------------------------------------------------------------
#endif
