#pragma once

#include <fstream>
#include <sstream>

#include "FileLogger.h"
#include "CommandLineReader.h"

namespace Utils
{
	bool fileExist(const std::string& fileName);

	int getFileSize(const std::string &fileName);

	template <class T>
	bool from_string(T& t,
		const std::string& s,
		std::ios_base& (*f)(std::ios_base&))
	{
		std::istringstream iss(s);
		return !(iss >> f >> t).fail();
	}

}