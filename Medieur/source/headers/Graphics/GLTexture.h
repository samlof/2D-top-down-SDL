#pragma once

#include <GL\glew.h>

namespace Graphics {
	struct GLTexture {
		GLuint id;
		int width, height;
	};
}