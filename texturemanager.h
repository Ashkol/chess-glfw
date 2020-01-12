#pragma once

#include <vector>
#include <string>

class TextureManager
{
public:
	TextureManager();
	unsigned int loadTexture(char const* path);
private:
	std::vector<unsigned char*> textures;
};

