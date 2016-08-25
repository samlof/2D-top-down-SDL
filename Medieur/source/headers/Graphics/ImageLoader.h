#pragma once

#include <string>

#include "Graphics\GLTexture.h"

namespace Graphics {
	namespace ImageLoader {
		GLTexture loadPNG(const std::string & pFilepath);
	}
}