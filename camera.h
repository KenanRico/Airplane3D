#ifndef CAMERA_H
#define CAMERA_H
//--------------------------------------------------------

#include <glm/glm.hpp>

class Vehicle;
class Camera{
	protected:
		struct CameraProperty{
			float FOV;
			float FOV_stretch;
			float render_distance;
		};
		struct CoordinateSystem{
			glm::vec3 front;
			glm::vec3 up;
			glm::vec3 right;
		};
	protected:
		struct CameraProperty property;
		struct CoordinateSystem coord;
		glm::vec3 position;
		glm::vec3 lens_pos;

	public:
		Camera(float, float, const glm::vec3&, const glm::vec3&);
		Camera(const Camera&);
		~Camera();
	private:
		Camera() = delete;
		Camera& operator=(const Camera&) = delete;

	public:
		void update(const Camera&);
	public:
		const glm::vec3& pos() const;
		const glm::vec3& lensPos() const;
		const glm::vec3& straightUp() const;
		float fov() const;
		float renderDistance() const;
		void printInfo() const;
	public:
		static void rotate(glm::vec3&, glm::vec3&, const glm::vec3&, float);

	friend class Vehicle;

};

//--------------------------------------------------------
#endif
