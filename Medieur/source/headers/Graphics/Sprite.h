#pragma once

#include <string>

#include <GL/glew.h>

#include "Rectangle.h"
#include "Graphics\GLTexture.h"

namespace Graphics {
	class Sprite
	{
	public:
		Sprite(const std::string& pFilepath, const float pX, const float pY, const float pWidth, const float pHeight);
		Sprite(const std::string& pFilepath, const Rectangle& pSrcRect) {}
		~Sprite();
		void draw(const int pX, const int pY);
		void draw(const int pX, const int pY, const Rectangle & pSrcRect);

	private:
		Rectangle mSourceRectangle;
		void init();

		float mX, mY, mWidth, mHeight;
		GLuint mVboId;
		GLTexture mTexture;
	};

}