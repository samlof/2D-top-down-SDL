#include "TextureCache.h"

#include "Graphics\ImageLoader.h"

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

Graphics::GLTexture TextureCache::getTexture(const std::string & pFilePath)
{
	if (mTextureMap.find(pFilePath) == mTextureMap.end()) {
		Graphics::GLTexture texture = Graphics::ImageLoader::loadPNG(pFilePath);

		mTextureMap.insert(make_pair(pFilePath, texture));
	}
	return mTextureMap.at(pFilePath);
}
