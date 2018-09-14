#ifndef GPU_BUFFER
#define GPU_BUFFER
//----------------------------------------------------------------


#include <glad/glad.h>

class GPUbuffer{
	private:
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		unsigned int indices_count;
		GLenum mode;

	public:
		GPUbuffer(float const *, unsigned int, unsigned int, unsigned int const *, unsigned int, unsigned int, GLenum);
		~GPUbuffer();
	private:
		GPUbuffer() = delete;
		GPUbuffer(const GPUbuffer&) = delete;
		GPUbuffer& operator=(const GPUbuffer&) = delete;

	public:
		void queryRenderInfo(unsigned int*, unsigned int*, unsigned int*, unsigned int*, GLenum*) const;
};

//----------------------------------------------------------------
#endif
