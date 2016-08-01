#pragma once

#include <string>

#include "Rectangle.h"

struct SDL_Texture;

class GroundEntity;

class Sprite
{
public:
	Sprite(const std::string& pFilepath, const int pX, const int pY, const int pWidth, const int pHeight);
	Sprite(const std::string& pFilepath, const Rectangle& pRectangle);

	void draw(const int pX, const int pY);
	void draw(const int pX, const int pY, const Rectangle & pSrcRect);

	Rectangle getRectangle() const { return mSourceRectangle; }

protected:
	Rectangle mSourceRectangle;
	SDL_Texture* mSpriteSheet;
};

