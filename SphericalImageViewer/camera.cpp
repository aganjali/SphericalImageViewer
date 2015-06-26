#include "camera.h"

camera::camera(GLuint w, GLuint h)
{
	w_width = w;
	w_height = h;

	yaw = 0.0f;
	roll = 0.0f;
	aspect = max_aspect;

	cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);
	update_viewMatrix();
	update_projectionMatrix(w, h);
}
void camera::update_viewMatrix()
{
	view_mat =	glm::lookAt(cameraPos, cameraPos + update_front(), cameraUp);
}

void camera::update_projectionMatrix(GLuint width, GLuint height)
{
	projection_mat =  glm::perspective(aspect, (GLfloat) width / (GLfloat) height, min_aspect, max_aspect);
}

glm::mat4 camera::get_viewMatrix()
{
	return	view_mat;
}

glm::mat4 camera::get_projectionMatrix()
{
	return  projection_mat;
}

glm::vec3 camera::update_front()
{
	glm::vec3 front;
	front.x = -sin(glm::radians(yaw)) * cos(glm::radians(roll));
	front.y = cos(glm::radians(yaw)) * cos(glm::radians(roll));
	front.z = sin(glm::radians(roll));
	cameraFront = glm::normalize(front);
	return cameraFront;
}
void camera::update_aspect(GLfloat delta_as)
{
	if (aspect >= min_aspect && aspect <= max_aspect)
		aspect += delta_as;
	
	if (aspect > max_aspect)
		aspect = max_aspect;

	if (aspect < min_aspect)
		aspect = min_aspect;

}

void camera::update_yaw(GLfloat delta_y)
{
	yaw += delta_y;

}
void camera::update_roll(GLfloat delta_r)
{
	roll += delta_r;
	if (roll > max_roll)
		roll = max_roll;

	if (roll < min_roll)
		roll = min_roll;
}

void camera::update_pitch(GLfloat delta_p)
{
	pitch += delta_p;
	
}

GLfloat  camera::get_pitch()
{
	return pitch; 
}

GLfloat  camera::get_yaw()
{
	return yaw;
}
GLfloat  camera::get_roll()
{
	return roll;
}
GLfloat  camera::get_aspect()
{
	return aspect;
}
glm::vec3  camera::get_front() const
{
	return cameraFront; 
}

void camera::set_pos(GLfloat x, GLfloat y, GLfloat z)
{ 
	cameraPos = glm::vec3(x, y, z);
}
glm::vec3 camera::get_pos() const
{ 
	return cameraPos; 
}

void camera::set_up(GLfloat x, GLfloat y, GLfloat z)
{
	cameraUp = glm::vec3(x, y, z);
}
glm::vec3  camera::get_up() const
{ 
	return cameraUp; 
}