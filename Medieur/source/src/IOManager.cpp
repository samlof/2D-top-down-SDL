#include "IOManager.h"

#include <fstream>

namespace IOManager {
	bool readFileToBinaryBuffer(const std::string & pFilePath, std::vector<unsigned char>& pBuffer)
	{
		std::ifstream file(pFilePath, std::ios::binary);
		if (file.fail()) {
			perror(pFilePath.c_str());
			return false;
		}

		file.seekg(0, std::ios::end);
		int filesize = file.tellg();
		file.seekg(0, std::ios::beg);
		filesize -= file.tellg();

		pBuffer.resize(filesize);

		file.read(reinterpret_cast<char*>(&(pBuffer[0])), pBuffer.size());

		file.close();
		return true;
	}
}