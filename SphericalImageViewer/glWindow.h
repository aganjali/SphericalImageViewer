#pragma once
#include "camera.h"
#include <stdlib.h>
#include <string>
#include "imageloader.h"

using namespace std;

class glWindow
{
	GLuint width, height;
	GLint posX, posY;
	string title;
	camera *cam;
	GLdouble sphereRadius;
	GLint oldX, newX, oldY, newY;
	GLint updateType;
	bool firstMouse;
	
	GLuint _textureId;
	GLUquadricObj *sphere = NULL;

	static glWindow* s_Window;
	static void mouseEvent(int button, int state, int x, int y);
	static void mouseMotion(int x, int y);
	static void reshape(int w, int h);
	static void update(int state, int ox, int nx, int oy, int ny);
	static void swapBuffers();
	static void display(void);
	static void set_window(glWindow* w);
	
public:
	camera* get_camera(){ return cam; }
	GLuint get_width(){ return width; }
	GLuint get_height(){ return height; }
	string get_title() const { return title; }
	
	GLint  get_updateType() { return updateType; }
	
	GLint get_posX(){ return posX; }
	GLint get_posY(){ return posY; }

	GLint get_oldX(){ return oldX; }
	GLint get_oldY(){ return oldY; }

	GLint get_newX(){ return newX; }
	GLint get_newY(){ return newY; }

	void set_oldX(GLint x){ oldX = x; }
	void set_oldY(GLint y){ oldY = y; }
		 						 
	void set_newX(GLint x){ newX = x; }
	void set_newY(GLint y){ newY = y; }
	
	void TexBind(Image* img);
	void init(Image* img);
	void run(){ glutMainLoop(); }

	glWindow(GLuint w, GLuint h, GLint x, GLint y, const char* t);
	~glWindow(){ SAFE_DELETE(cam); };
};

