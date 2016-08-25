#pragma once

#include<string>

#include "Graphics\GLTexture.h"
struct SDL_Texture;

class Rectangle;
class World;

namespace Graphics {
	GLTexture loadImage(const std::string& pFilepath);
	void init();

	void renderTexture(SDL_Texture * pTexture,
		const Rectangle & pSourceRectangle,
		const Rectangle & pDestinationRectangle);

	void clear();
	void renderPresent();

	void targetWorldTexture();
	void changeWorldTexture(int pWidth, int pHeight);
	void resetTarget();

	void quit();
}