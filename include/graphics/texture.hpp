#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

// A helper class to easily load and use 2D textures
class Texture
{
public:
	unsigned int texID;

	Texture();

	Texture(std::string filename, bool stbiFlipOnLoad = false);

	void bindTexture();
};

#endif