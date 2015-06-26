#pragma once
#include "helper.h"

#define min_aspect 10.0f
#define max_aspect 100.0f

#define min_roll -89.0f
#define max_roll 89.0f

class camera
{
	glm::vec3 cameraPos, cameraFront, cameraUp;

	GLfloat yaw, pitch, roll ;

	GLuint w_width, w_height;
	GLfloat aspect;
	glm::mat4 view_mat, projection_mat;

public:
	camera(GLuint w, GLuint h);
	~camera(){};
	
	void set_pos(GLfloat x, GLfloat y, GLfloat z);
	void set_up(GLfloat x, GLfloat y, GLfloat z);

	glm::vec3  get_up() const;
	glm::vec3 get_pos() const;
	glm::vec3  get_front() const;

	GLfloat  get_pitch();
	GLfloat  get_yaw();
	GLfloat  get_roll();
	GLfloat  get_aspect();
	
	void update_aspect(GLfloat delta_as);

	void update_yaw(GLfloat delta_y);
	void update_roll(GLfloat delta_r);
	void update_pitch(GLfloat delta_p);

	glm::vec3 update_front();

	glm::mat4 get_viewMatrix();
	glm::mat4 get_projectionMatrix();
	
	void update_viewMatrix();
	void update_projectionMatrix(GLuint width, GLuint height);
	
};

