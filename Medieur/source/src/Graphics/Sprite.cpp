#include "Graphics\Sprite.h"

#include <cstddef>

#include "Graphics\Graphics.h"
#include "Graphics\Vertex.h"

#include "Rectangle.h"
#include "units.h"

namespace Graphics {
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

		vertexData[0].position = Position{ 0, 1 };
		vertexData[1].position = Position{ 1, 1 };
		vertexData[2].position = Position{ -1, 1 };
		vertexData[3].position = Position{ 1, 1 };
		vertexData[4].position = Position{ 0, 1 };
		vertexData[5].position = Position{1, 1};

		for (size_t i = 0; i < 6; i++)
		{
			vertexData[i].color = Color{ 255, 0, 0, 1 };
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
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

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
}