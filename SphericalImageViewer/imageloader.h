#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <GL/glut.h>


class Image 
{
	public:
		Image(unsigned char* ps, int w, int h, int ch);
		~Image();

		unsigned char* pixels;
		int width;
		int height;

		unsigned short int bpp; //bits per pixels   unsigned short int
		unsigned long size;     //length of the file
		int channels;      //the channels of the image 3 = RGA 4 = RGBA
		GLuint type;
};

Image* loadImg(const char* filename);

GLuint loadTextureFromImage(Image* image);

#endif
