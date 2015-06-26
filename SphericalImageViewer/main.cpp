#pragma once 

#include "glWindow.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glWindow* window = new glWindow(1024, 768, 100, 100, "Spherical Image Viewer");
	string filename;
	Image* img = NULL;
	do
	{
		std::cout << "Please Enter file name: ";
		std::cin >> filename;
		std::cout << endl;
		
		img = loadImg(filename.c_str());

	} while (!img);

	std::cout << "image size: " << img->width << "x" << img->height << "\tchannels: " << img->channels;

	window->init(img);
	window->run();

	SAFE_DELETE(window);
	SAFE_DELETE(img);
	return 0;
}
