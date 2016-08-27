#pragma once

#include <string>

#include "Graphics\GLTexture.h"

namespace ResourceManager {
	Graphics::GLTexture getTexture(const std::string & pFilePath);
}