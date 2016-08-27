#include "ResourceManager.h"

#include "TextureCache.h"

namespace ResourceManager {
	namespace {
		TextureCache textureCache;
	}


	Graphics::GLTexture getTexture(const std::string & pFilePath)
	{
		return textureCache.getTexture(pFilePath);
	}
}