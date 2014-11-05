#include "Utils.h"

namespace Utils
{

	bool fileExist(const std::string& fileName) {
		FILE *file;
		if (fopen_s(&file, fileName.c_str(), "r")) {
			fclose(file);
			return true;
		}
		else {
			return false;
		}
	}

	int getFileSize(const std::string &fileName)
	{
		std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);

		if (!file.is_open())
		{
			return -1;
		}

		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.close();

		return fileSize;
	}

}