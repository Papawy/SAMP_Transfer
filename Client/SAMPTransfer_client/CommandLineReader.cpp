#include "CommandLineReader.h"

namespace Utils
{
	CommandLineReader::CommandLineReader()
	{
	}

	CommandLineReader::~CommandLineReader()
	{
	}

	size_t CommandLineReader::readLine(std::string line)
	{
		m_arguments.clear();

		size_t pos;
		std::string substr;

		while ((pos = line.find(" -")) != std::string::npos)
		{
			substr = line.substr(0, pos);

			this->splitArguments(substr);
			line.erase(0, pos + 2);
		}

		substr = line.substr(pos + 1);
		this->splitArguments(substr);
		return m_arguments.size();
	}

	bool CommandLineReader::argumentExist(std::string key)
	{
		return m_arguments.count(key) > 0;
	}

	bool CommandLineReader::argumentHasValue(std::string key)
	{
		return m_arguments.find(key)->second.length() > 0;
	}

	std::string CommandLineReader::getArgumentValue(std::string key)
	{
		return m_arguments.find(key)->second;
	}

	void CommandLineReader::splitArguments(std::string arguments)
	{
		std::pair<std::string, std::string> pair;
		size_t pos = arguments.find(' ');
		if (pos != std::string::npos)
		{
			pair = std::pair<std::string, std::string>(arguments.substr(0, pos), arguments.substr(pos + 1));
		}
		else
		{
			pair = std::pair<std::string, std::string>(arguments, "");
		}

		m_arguments.insert(pair);
	}
}

