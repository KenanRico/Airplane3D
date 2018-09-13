#ifndef CAMERA_H
#define CAMERA_H
//--------------------------------------------------------
#include <glm/glm.hpp>


class Camera{
	private:
		struct CameraProperty{
			float FOV;
			float render_distance;
			float speed;
			const float sensitivity;
		};
		struct CoordinateSystem{
			glm::vec3 front;
			glm::vec3 up;
			glm::vec3 right;
		};
	private:
		struct CameraProperty property;
		struct CoordinateSystem coord;
		glm::vec3 position;
		glm::vec3 lens_pos;

	public:
		Camera(float, float, float, float, const glm::vec3&);
		~Camera();
	private:
		Camera() = delete;
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

	public:
		void update();
	public:
		const glm::vec3& pos() const;
		const glm::vec3& lensPos() const;
		const glm::vec3& straightUp() const;
		float fov() const;
		float renderDistance() const;
};

//--------------------------------------------------------
#endif
