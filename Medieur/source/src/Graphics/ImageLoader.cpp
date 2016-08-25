#include "Graphics\ImageLoader.h"

#include "../../dependency/picoPNG.h"

#include "IOManager.h"

namespace Graphics {
	namespace ImageLoader {
		GLTexture loadPNG(const std::string & pFilepath)
		{
			GLTexture texture = {};

			std::vector<unsigned char> out;
			unsigned long width, height;
			std::vector<unsigned char> in;
			bool fileReadsuccess = IOManager::readFileToBinaryBuffer(pFilepath, in);
			if (!fileReadsuccess) {
				printf("Failed to read png file!\n");
				return GLTexture();
			}
			int errorcode = decodePNG(out, width, height, &(in[0]), in.size(), true);
			if (errorcode != 0) {
				printf("Error in decodePNG with code: %i\n", errorcode);
			}
			texture.width = width;
			texture.height = height;

			glGenTextures(1, &texture.id);

			glBindTexture(GL_TEXTURE_2D, texture.id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			return texture;
		}
	}
}