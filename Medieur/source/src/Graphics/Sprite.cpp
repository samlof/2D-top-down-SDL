#include "Graphics\Sprite.h"

#include "Graphics\Graphics.h"
#include "Graphics\Vertex.h"

#include "Rectangle.h"
#include "units.h"

Sprite::Sprite(const std::string & pFilepath, const Rectangle & pRectangle)
	:
	mSourceRectangle(pRectangle), mVboId(0)
{
	
}

Sprite::~Sprite()
{
	if (mVboId != 0) {
		glDeleteBuffers(1, &mVboId);
		mVboId = 0;
	}
}

void Sprite::init()
{
	if (mVboId == 0) {
		glGenBuffers(1, &mVboId);
	}

	Vertex vertexData[6];

	vertexData[1].position = { mSourceRectangle.getX(), mSourceRectangle.getY() };

	for (size_t i = 0; i < 6; i++)
	{
		vertexData[i].color = { 255, 0, 0, 1 };
	}

	glBindBuffer(GL_ARRAY_BUFFER, mVboId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData[0], GL_STATIC_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw(const int pX, const int pY)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glEnableVertexAttribArray(0);

	// Position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw(const int pX, const int pY, const Rectangle & pSourceRect)
{
	/*
	Graphics::renderTexture(
		mSpriteSheet,
		pSourceRect,
		Rectangle(pX, pY, units::kTileSize, units::kTileSize)
	);
	*/
}
