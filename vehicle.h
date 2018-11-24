#ifndef VEHICLE_H
#define VEHICLE_H
//---------------------------------------------------------------------

#include "camera.h"
#include "object.h"
#include "gpubuffer.h"

#include <string>
#include <vector>

#include <glm/glm.hpp>


class Vehicle : public Object{
	private:
		enum CameraID {FP=0, TP=1, rear=2};
	private:
		struct Orientation{
			glm::vec3 front;
			glm::vec3 up;
			glm::vec3 right;
		};
		struct Velocity{
			float magnitude;
			float max;
			float min;
		};
		struct Control{
			float max_roll_angle;
			float pitch_sensitivity;
			float roll_sensitivity;
		};
		struct Cameras{
			Camera views[3];
			Camera* current;
		};
	private:
		struct Orientation orientation;
		struct Velocity velocity;
		struct Control controller;
		struct Cameras cameras;

	public:
		Vehicle(GPUbuffer const *, unsigned int, const glm::vec3&, float, const glm::vec3&, float, float, float, float, float, float);
		~Vehicle();
	private:
		Vehicle() = delete;
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator=(const Vehicle&) = delete;

	public:
		void updateProperties() override;
		void computeTransformations(const Camera&) override;
		const Camera& viewingCamera() const;
		const Camera& fpCamera() const;
		const Camera& tpCamera() const;
		const Camera& rearCamera() const;
		void control(std::vector<Object*>*) override;
};

//---------------------------------------------------------------------
#endif
