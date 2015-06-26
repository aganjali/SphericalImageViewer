#pragma once

#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sys/stat.h>

inline bool file_exist(const char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}
#define SAFE_DELETE(p)     do { if ((p) != 0) { delete p; (p) = NULL; } } while(0)

//#define bound(x, max, min) x = (x > max) ? max : ((x < min) ? min : x)

#ifndef Debug
//#define Debug
#endif

#define PRINT_ERROR(_msg)  std::cout << _msg << "\n";	

#if defined(Debug)
#define ASSERT(_failed, _msg)                     \
if (_failed)                                    \
{                                                   \
	PRINT_ERROR(_msg);		\
	__debugbreak();									\
}
#endif

enum
{
	PAN = 1,
	ROTATE = 2
};
