#pragma once

#include <string>
#include <map>

#define SAMP_PARAM_DEBUG "d"
#define SAMP_PARAM_CONNECT "c"
#define SAMP_PARAM_UNAME "n"
#define SAMP_PARAM_ADDRESS "h"
#define SAMP_PARAM_PORT "p"
#define SAMP_PARAM_PASS "z"

namespace Utils
{
	class CommandLineReader
	{
	public:
		CommandLineReader();
		~CommandLineReader();

		size_t readLine(std::string line);

		bool argumentExist(std::string key);

		bool argumentHasValue(std::string key);

		std::string getArgumentValue(std::string key);

	protected:
		void splitArguments(std::string arguments);

		std::map<std::string, std::string> m_arguments;
	};
}