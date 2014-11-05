#pragma once

#include <iostream>
#include <vector>

#include <SFML\Network.hpp>

#include "Utils.h"

#define SAMP_PARAM_DEBUG "d"
#define SAMP_PARAM_CONNECT "c"
#define SAMP_PARAM_UNAME "n"
#define SAMP_PARAM_ADDRESS "h"
#define SAMP_PARAM_PORT "p"
#define SAMP_PARAM_PASS "z"

class Client
{
public:
	Client(sf::Time receiveLimit);
	~Client();

	struct FileDL
	{
		std::string filePath;
		int fileSize;
		bool inClientPC;
	};

	bool readCommandLine(std::string line);

	bool connectToSampServer();

	bool listenToFtpInfos();
	bool listenToNeededFiles();
	bool checkPresentFiles();

	bool connectToFtp();
	bool downloadNeededFiles();
	

private:
	sf::Time m_receiveLimit;

	sf::Ftp			m_ftp;
	sf::TcpSocket	m_tcpSocket;

	sf::IpAddress	m_sampServerIp;
	unsigned short	m_sampServerPort;

	sf::IpAddress	m_ftpServerIp;
	unsigned short	m_ftpServerPort;

	std::vector<FileDL> m_filesToDL;

	Utils::FileLogger	m_fileLog;
};