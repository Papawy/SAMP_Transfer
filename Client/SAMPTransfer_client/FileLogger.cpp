#include "FileLogger.h"

namespace Utils
{
	FileLogger::FileLogger()
	{
		m_showDate = true;
		m_showTime = true;
	}

	FileLogger::FileLogger(std::string fileName)
	{
		m_showDate = true;
		m_showTime = true;

		m_fileName = fileName;

		m_logFile.open(fileName, std::ios::out | std::ios::app);

		if (m_logFile.is_open() != true)
		{
			if (m_debug == true)
			{
				std::cerr << "[FileLogger] ERROR : Unable to open file : \" " << fileName << " \" )." << std::endl;
			}
		}

		if (m_debug == true)
		{
			std::cout << "[FileLogger] Writing in file (\" " << m_fileName << "\" ) :" << std::endl;
		}
	}

	FileLogger::~FileLogger()
	{
		m_logFile.close();
	}

	void FileLogger::setDebugMode(bool debug)
	{
		m_debug = debug;
	}

	void FileLogger::showDate(bool show)
	{
		m_showDate = show;
	}

	void FileLogger::showTime(bool show)
	{
		m_showTime = show;
	}

	bool FileLogger::log(std::string log)
	{
		if (m_logFile.is_open())
		{
			time_t timet;
			struct tm currentTime;
			timet = time(0);
			localtime_s(&currentTime, &timet);

			if (m_showDate == true)
			{
				m_logFile << "[" << currentTime.tm_mday << "/" << currentTime.tm_mon << "/" << currentTime.tm_year - 100 << "] ";
			}
			if (m_showTime == true)
			{
				m_logFile << "[" << currentTime.tm_hour << ":" << currentTime.tm_min << ":" << currentTime.tm_sec << "] ";
			}

			m_logFile << log << std::endl;

			if (m_debug == true)
			{
				std::cout << "[FileLogger] " << log << std::endl;
			}

			//m_logFile.close();

			return true;

		}
		else
		{
			if (m_debug == true)
			{
				std::cerr << "[FileLogger] ERROR : Unable to write in file (\" " << m_fileName << "\" ) ." << std::endl;
			}
			return false;
		}

	}

	bool FileLogger::changeLogFile(std::string fileName)
	{
		if (m_logFile.is_open())
		{
			m_logFile.close();
		}

		m_fileName = fileName;

		m_logFile.open(fileName, std::ios::out | std::ios::app);

		if (m_logFile.is_open() != true)
		{
			if (m_debug == true)
			{
				std::cerr << "[FileLogger] ERROR : Unable to open file : \" " << fileName << " \"." << std::endl;
			}
			return false;
		}

		if (m_debug == true)
		{
			std::cout << "[FileLogger] Now writing in file (\" " << m_fileName << "\" ) :" << std::endl;
		}

		return true;
	}

	std::ofstream* FileLogger::directAccess()
	{
		return &m_logFile;
	}
}