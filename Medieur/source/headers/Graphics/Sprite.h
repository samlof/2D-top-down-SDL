#pragma once

#include <string>

#include <GL/glew.h>

#include "Rectangle.h"

namespace Graphics {
	class Sprite
	{
	public:
		Sprite(const std::string& pFilepath, const Rectangle& pRectangle);
		Sprite(const std::string& pFilepath, const int pX, const int pY, const int pWidth, const int pHeight)
			: Sprite(pFilepath, Rectangle{ pX, pY, pWidth, pHeight }) {}
		~Sprite();
		void draw(const int pX, const int pY);
		void draw(const int pX, const int pY, const Rectangle & pSrcRect);

		Rectangle getRectangle() const { return mSourceRectangle; }

		void init();
	private:
		Rectangle mSourceRectangle;
		GLuint mVboId;
	};

}