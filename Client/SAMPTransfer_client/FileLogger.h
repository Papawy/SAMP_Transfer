#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

namespace Utils
{
	class FileLogger
	{
	public:
		FileLogger();
		FileLogger(std::string fileName);
		~FileLogger();

		void setDebugMode(bool debug = false);

		bool changeLogFile(std::string fileName);

		void showTime(bool show);

		void showDate(bool show);

		bool log(std::string log);

		std::ofstream* directAccess();

	protected:

		bool m_debug;

		bool m_showDate;
		bool m_showTime;

		std::string m_fileName;

		std::ofstream m_logFile;

	};
}