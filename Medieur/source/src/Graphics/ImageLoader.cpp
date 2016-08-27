#include "Graphics\ImageLoader.h"

#include <GL\glew.h>

#include "../../dependency/picoPNG.h"

#include "IOManager.h"

namespace Graphics {
	namespace ImageLoader {
		GLTexture loadPNG(const std::string & pFilepath)
		{
			printf("Loaded Image: %s!\n", pFilepath.c_str());

			GLTexture texture = {};

			std::vector<unsigned char> out;
			unsigned long width, height;
			std::vector<unsigned char> in;
			bool fileReadsuccess = IOManager::readFileToBinaryBuffer(pFilepath, in);
			if (!fileReadsuccess) {
				printf("Failed to read png file!\n");
				return texture;
			}
			int errorcode = decodePNG(out, width, height, &(in[0]), in.size(), true);
			if (errorcode != 0) {
				printf("Error in decodePNG with code: %i\n", errorcode);
				return texture;
			}
			texture.width = width;
			texture.height = height;

			glGenTextures(1, &texture.id);

			glBindTexture(GL_TEXTURE_2D, texture.id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			return texture;
		}
	}
}