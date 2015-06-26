#include "imageloader.h"
#include <jpeg/SOIL.h>

using namespace std;

Image::Image(unsigned char* ps, int w, int h, int ch) : pixels(ps), width(w), height(h), channels(ch)
{

}

Image::~Image() 
{

}

namespace 
{
  int toInt(const char* bytes) 
  {
      return (int)(((unsigned char)bytes[3] << 24) |          ((unsigned char)bytes[2] << 16) |          ((unsigned char)bytes[1] << 8) |          (unsigned char)bytes[0]);
  }

  int readInt(ifstream &input) 
  {
      char buffer[4];
      input.read(buffer, 4);
      return toInt(buffer);
  }
}

Image* loadImg(const char* filename)
{
	int w, h, ch;
	auto data = SOIL_load_image(filename, &w, &h, &ch, SOIL_LOAD_RGBA);
	if (!data)
	{
		std::cerr << "could not load file!\n";
		return 0;
	}
	return new Image(data, w, h, ch);
}

GLuint loadTextureFromImage(Image* image) 
{
  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
  return textureId;
}
