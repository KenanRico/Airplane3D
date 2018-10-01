#include "vehicle.h"
#include "camera.h"
#include "gamesystem.h"
#include "eventhandler.h"
#include "logger.h"

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

//#define OLD


Vehicle::Vehicle(
	GPUbuffer const * gb, unsigned int s, const glm::vec3& p, float si,
	const glm::vec3& _front, float mag, float max, float min,
	float mra, float ps, float rs
): 
Object(gb, s, p, si),
velocity((struct Velocity){glm::normalize(_front), glm::normalize(glm::cross(_front, glm::vec3(1.0f, 1.0f, 1.0f))), glm::normalize(glm::cross(velocity.front, velocity.up)), mag, max, min}),
control((struct Control){mra, ps, rs}),
cameras(
	(struct Cameras){
		{Camera(40.0f, 250.0f, p, velocity.front), Camera(60.0f, 250.0f, p, velocity.front), Camera(60.0f, 250.0f, p, -velocity.front)},
		&cameras.views[FP]
	}
),
control_lock(false){
	//nothin
}

Vehicle::~Vehicle(){
	//nothin
}


void rotate(glm::vec3&, glm::vec3&, const glm::vec3&, float);
void Vehicle::update(const Camera& camera){
	if(control_lock){
		/*-------handle input, update object-------*/
		if(EventHandler::keyDown(EventHandler::W)){
			rotate(velocity.front, velocity.up, velocity.right, -0.1f);
		}
		if(EventHandler::keyDown(EventHandler::A)){
			rotate(velocity.right, velocity.up, velocity.front, 0.1f);
		}
		if(EventHandler::keyDown(EventHandler::S)){
			rotate(velocity.front, velocity.up, velocity.right, 0.1f);
		}
		if(EventHandler::keyDown(EventHandler::D)){
				rotate(velocity.right, velocity.up, velocity.front, -0.1f);
		}
		float& speed = velocity.magnitude;
		if(EventHandler::keyDown(EventHandler::SPACE)){
			speed += 0.0001f;
		}else{
			speed -= 0.0003f;
		}
		const float& max = velocity.max;
		const float& min = velocity.min;
		if(speed>max){
			speed = max;
		}else if(speed<min){
			speed = min;
		}
		position.current += velocity.magnitude * velocity.front;
		if(EventHandler::keyClicked(EventHandler::C)){
			cameras.current = &cameras.views[(cameras.current-cameras.views+1) % 3];
		}
	}

	/*----update cams------*/
	Camera* fp = &cameras.views[FP];
	Camera* tp = &cameras.views[TP];
	Camera* r = &cameras.views[rear];
	fp->position = position.current;
	fp->coord.front = velocity.front;
	fp->coord.up = velocity.up;
	fp->coord.right = velocity.right;
	fp->lens_pos = fp->position + fp->coord.front;
	tp->position = position.current - velocity.front*(2.0f+velocity.magnitude*10.0f);
	tp->coord.front = velocity.front;
	tp->coord.up = velocity.up;
	tp->coord.right = velocity.right;
	tp->lens_pos = tp->position + tp->coord.front;
	r->position = position.current;
	r->coord.front = -velocity.front;
	r->coord.up = velocity.up;
	r->coord.right = -velocity.right;
	r->lens_pos = r->position + r->coord.front;

	/*------update transformations--------*/
	transformation.model = glm::translate(transformation.model, position.last);
	transformation.model = glm::scale(transformation.model, size.current/size.last);
	transformation.model = glm::translate(transformation.model, position.last);
	transformation.model = glm::translate(transformation.model, position.current-position.last);
	transformation.view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	transformation.projection = glm::perspective(
		glm::radians(camera.fov()),
		(float)GameSystem::windowW()/(float)GameSystem::windowH(),
		0.1f,
		camera.renderDistance()
	);

	/*------apply transformation---------*/
	applyTransformations();
}

void Vehicle::render() const{
	if(cameras.current!=&cameras.views[FP]){
		Object::render();
	}
}

const Camera& Vehicle::viewingCamera() const{
	return *cameras.current;
}

void Vehicle::controlLock(bool lock){
	control_lock = lock;
}


void rotate(glm::vec3& vec1, glm::vec3& vec2, const glm::vec3& ref, float angle_degree){
	//define 3x3 identity matrix
	glm::mat3 identity = glm::mat3();
	//define 3x3 lever matrix
	float L[9] = {0.0f,ref.z,-ref.y, -ref.z,0.0f,ref.x, ref.y,-ref.x,0.0f};
	glm::mat3 lever(glm::make_mat3(L));
	//degree to radian
	float angle = glm::radians(angle_degree);
	vec1 = glm::normalize(vec1 * (identity+sin(angle)*lever+(1-cos(angle))*(lever*lever)));
	vec2 = glm::normalize(vec2 * (identity+sin(angle)*lever+(1-cos(angle))*(lever*lever)));
}
