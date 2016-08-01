#pragma once

#include<string>

struct SDL_Texture;

class Rectangle;
class World;

namespace Graphics {
	SDL_Texture* loadImage(const std::string& pFilename);
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