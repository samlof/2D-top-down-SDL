#include "Graphics\Sprite.h"

#include <cstddef>

#include <GL\glew.h>

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
		float x = -1.0f, y = -1.0f, width = 2.0f, height = 2.0f;
		//First Triangle
		vertexData[0].position.x = x + width;
		vertexData[0].position.y = y + height;

		vertexData[1].position.x = x;
		vertexData[1].position.y = y + height;

		vertexData[2].position.x = x;
		vertexData[2].position.y = y;

		//Second Triangle
		vertexData[3].position.x = x;
		vertexData[3].position.y = y;

		vertexData[4].position.x = x + width;
		vertexData[4].position.y = y;

		vertexData[5].position.x = x + width;
		vertexData[5].position.y = y + height;

		for (size_t i = 0; i < 6; i++)
		{
			vertexData[i].color = Color{ 255, 0, 0, 1 };
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

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