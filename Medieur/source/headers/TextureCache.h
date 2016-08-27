#pragma once

#include <unordered_map>
#include <string>

#include "Graphics\GLTexture.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Graphics::GLTexture getTexture(const std::string& pFilePath);
private:
	std::unordered_map<std::string, Graphics::GLTexture> mTextureMap;
};

