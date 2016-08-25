#pragma once

#include <GL\glew.h>


namespace Graphics {
	struct Position {
		float x, y;
	};
	struct Color {
		GLubyte r, g, b, a;
	};

	struct Vertex {
		Position position;
		Color color;
	};
}