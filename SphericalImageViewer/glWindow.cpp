#include "glWindow.h"
#include <math.h>
glWindow *glWindow::s_Window = NULL;

glWindow::glWindow(GLuint w, GLuint h, GLint x, GLint y, const char* t) :posX(x), posY(y), width(w), height(h), title(t){
	oldX = 0;
	newX = 0;
	oldY = 0;
	newY = 0;
	updateType = 0;
	cam = new camera(w, h);
	cam->set_pos(0.0f, 0.0f, 0.0f);
	firstMouse = true;

	set_window(this);
}


void glWindow::TexBind(Image* img)
{

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);

	glDisable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);


	if (!img)
	{
		_textureId = -1;
		return;
	}

	_textureId = loadTextureFromImage(img);

	/*delete img;*/



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);

	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricOrientation(sphere, GLU_INSIDE);

	gluQuadricNormals(sphere, GLU_SMOOTH);

}
void glWindow::init(Image* img)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(posX, posY);
	glutCreateWindow(title.c_str());
	glutDisplayFunc(glWindow::display);
	glutReshapeFunc(glWindow::reshape);
	glutMouseFunc(glWindow::mouseEvent);
	glutMotionFunc(glWindow::mouseMotion);
	glEnable(GL_DEPTH_TEST);	
	TexBind(img);
}



void glWindow::update(int state, int lastX, int x, int lastY, int y)
{
	GLfloat xoffset = x - lastX;
	GLfloat yoffset = y - lastY;

	GLfloat sensitivity = 0.002f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	switch (state)
	{
		case PAN:

			break;
		case ROTATE:

			s_Window->get_camera()->update_yaw(xoffset);
			s_Window->get_camera()->update_roll(yoffset);
			s_Window->get_camera()->update_viewMatrix();

			break;
	}
}

void glWindow::reshape(int width, int height)
{
	auto cam = s_Window->get_camera();
	cam->update_projectionMatrix(width, height);
	cam->update_viewMatrix();

	glm::vec3 pos = cam->get_pos();
	glm::vec3 front = pos + cam->get_front();
	glm::vec3 up = cam->get_up();

	s_Window->width = width;
	s_Window->height = height;
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cam->get_aspect(), (GLdouble) width / (GLdouble) height, min_aspect, max_aspect);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(front.x, front.y, front.z, pos.x, pos.y, pos.z, up.x, up.y, up.z);
	glScalef(-1, 1, -1);
}

void glWindow::swapBuffers(void)
{
	glutSwapBuffers();
}

void glWindow::display()
{
	update(s_Window->updateType, s_Window->oldX, s_Window->newX, s_Window->oldY, s_Window->newY);
	auto cam = s_Window->get_camera();
	glm::vec3 pos = cam->get_pos();
	glm::vec3 front = pos + cam->get_front();
	glm::vec3 up = cam->get_up();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, s_Window->_textureId);
	glPushMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cam->get_aspect(), (GLdouble) s_Window->width / (GLdouble) s_Window->height, min_aspect, max_aspect);
	
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	
	gluLookAt(front.x, front.y, front.z, pos.x, pos.y, pos.z, up.x, up.y, up.z);
	glScalef(-1, 1, -1);

	
	gluSphere(s_Window->sphere, 50, 100, 100);

	glPopMatrix();
	glFlush();
	swapBuffers();
	glutPostRedisplay();

	
}
void glWindow::set_window(glWindow* w)
{
	s_Window = w;
}

void glWindow::mouseEvent(int button, int state, int x, int y)
{

	if (s_Window->firstMouse)
	{
		s_Window->oldX = x;
		s_Window->oldX = y;
		s_Window->firstMouse = false;
	}

	s_Window-> updateType = 0;
	if (state == GLUT_DOWN)
	{
		s_Window->oldX = x;
		s_Window->oldY = y;
		s_Window->newX = x;
		s_Window->newY = y;
	}
	if (state == GLUT_UP)
	{
		s_Window->oldX = s_Window->newX;
		s_Window->oldY = s_Window->newY;
	}
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			s_Window->updateType = ROTATE;
			break;
		case GLUT_RIGHT_BUTTON:
			s_Window->updateType = PAN;
			break;
		case 3:
			s_Window->get_camera()->update_aspect(-1);
			s_Window->get_camera()->update_projectionMatrix(s_Window->width, s_Window->height);
			break;
		case 4:
			s_Window->get_camera()->update_aspect(1);
			s_Window->get_camera()->update_projectionMatrix(s_Window->width, s_Window->height);
			break;
	};

	
}
//
void glWindow::mouseMotion(int x, int y)
{
	s_Window->newX = x;
	s_Window->newY = y;
}