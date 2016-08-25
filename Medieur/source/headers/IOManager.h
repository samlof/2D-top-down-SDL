#pragma once

#include <vector>


namespace IOManager {
	bool readFileToBinaryBuffer(const std::string& pFilePath, std::vector<unsigned char>& pBuffer);
}