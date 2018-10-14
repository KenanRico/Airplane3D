#ifndef VEHICLE_H
#define VEHICLE_H
//---------------------------------------------------------------------

#include "camera.h"
#include "object.h"
#include "gpubuffer.h"
#include "weapon.h"

#include <string>

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
		struct Control control;
		struct Cameras cameras;
		Weapon weapon;

	public:
		Vehicle(GPUbuffer const *, unsigned int, const glm::vec3&, float, const glm::vec3&, float, float, float, float, float, float);
		~Vehicle();
	private:
		Vehicle() = delete;
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator=(const Vehicle&) = delete;

	public:
		void defineWeapon(GPUbuffer const *, const std::string&, const std::string&, float, float);
		void update(const Camera&) override;
		void render() const override;
		const Camera& viewingCamera() const;
	private:
		void computeTransformations(const Camera&, struct Transformation*) override;
};

//---------------------------------------------------------------------
#endif
