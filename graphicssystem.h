#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H
//---------------------------------------------------------------

#include "object.h"

#include <vector>

class GraphicsSystem{
	private:
		enum class LightingState { OFF, ON };
		enum class BlinnPhongState { OFF, ON };
		enum class GammaCorrectionState { OFF, DEFAULT, CUSTOM };
		enum class HDRState {OFF, ON};

		struct SystemLighting{
			LightingState state;
		};
		struct BlinnPhong{
			BlinnPhongState state;
		};
		struct Gamma{
			GammaCorrectionState state;
		};
		struct HDR{
			HDRState state;
			unsigned int FBO;
			unsigned int color_buffer;
			unsigned int shader;
		};

	private:
		std::vector<unsigned int> client_shader_pool;
		std::vector<Object*> const * objects;
		SystemLighting system_lighting;
		BlinnPhong blinn_phong;
		Gamma gamma;
		HDR hdr;
		
	public:
		GraphicsSystem();
		~GraphicsSystem();
	private:
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;

	public:
		void setClientShaders(const std::vector<unsigned int>&);
		void init(const std::vector<Object*>&, unsigned int);
		void update();
		void commit() const;
		unsigned int getHdrColorBuffer() const;

};

//---------------------------------------------------------------
#endif
