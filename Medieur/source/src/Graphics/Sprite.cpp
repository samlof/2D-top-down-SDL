#include "Graphics\Sprite.h"

#include "Graphics\Graphics.h"

#include "units.h"


Sprite::Sprite(const std::string& pFilepath, int pX, int pY, int pWidth, int pHeight)
	: Sprite(pFilepath, Rectangle{pX, pY, pWidth, pHeight})
{

}

Sprite::Sprite(const std::string & pFilepath, const Rectangle & pRectangle)
	:

	mSourceRectangle(pRectangle), mVbo(0)
{
}

void Sprite::draw(const int pX, const int pY)
{
	Graphics::renderTexture(
		mSpriteSheet,
		mSourceRectangle,
		Rectangle(pX, pY, units::kTileSize, units::kTileSize)
	);
}

void Sprite::draw(const int pX, const int pY, const Rectangle & pSourceRect)
{
	Graphics::renderTexture(
		mSpriteSheet,
		pSourceRect,
		Rectangle(pX, pY, units::kTileSize, units::kTileSize)
	);
}
