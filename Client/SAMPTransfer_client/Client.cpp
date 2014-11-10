#include "Client.h"

Client::Client(sf::Time receiveLimit)
{
	m_receiveLimit = receiveLimit;
	m_tcpSocket.setBlocking(false);
	m_fileLog.changeLogFile("TransferLog.txt");
}

Client::~Client()
{
	
}

bool Client::readCommandLine(std::string line)
{
	m_fileLog.log(line);

	m_cmdReader.readLine(line);
	m_fileLog.log("Getting infos from command line...");
	m_sampServerIp = m_cmdReader.getArgumentValue(SAMP_PARAM_ADDRESS);
	m_fileLog.log("Getting ip : " + m_sampServerIp.toString());
	if (Utils::from_string<unsigned short>(m_sampServerPort, m_cmdReader.getArgumentValue(SAMP_PARAM_PORT), std::dec) == false)
	{
		m_fileLog.log("Fail while converting string to unsigned short.");
	}
	m_fileLog.log("Getting port : " + std::to_string(m_sampServerPort));
	if (m_cmdReader.argumentExist(SAMP_PARAM_PASS))
	{
		m_sampServerPass = m_cmdReader.getArgumentValue(SAMP_PARAM_PASS);
		m_fileLog.log("Getting server password : " + m_sampServerPass);
	}
	return true;
}

bool Client::connectToSampServer()
{
	sf::Socket::Status status = m_tcpSocket.connect(m_sampServerIp, m_sampServerPort);
	if (status != sf::Socket::Done)
	{
		return false;
	}
	return true;
}

bool Client::listenToFtpInfos()
{
	sf::Packet ftpPacket;
	sf::Clock stopSocket;
	while (stopSocket.getElapsedTime() < m_receiveLimit)
	{
		if (m_tcpSocket.receive(ftpPacket) != sf::Socket::Done)
		{
			break;
		}
	}
	std::string tmp_ip;
	if (ftpPacket >> tmp_ip >> m_ftpServerPort)
	{
		m_ftpServerIp = tmp_ip;
		return true;
	}
	return false;
}

bool Client::listenToNeededFiles()
{
	sf::Packet filesPathPacket;
	sf::Clock stopSocket;
	while (stopSocket.getElapsedTime() < m_receiveLimit)
	{
		if (m_tcpSocket.receive(filesPathPacket) == sf::Socket::Done)
		{
			break;
		}
	}

	int nbrFiles;
	if (filesPathPacket >> nbrFiles)
	{
		Client::FileDL tmpFile;

		for (int i = 0; i < nbrFiles; i++)
		{
			if (filesPathPacket >> tmpFile.filePath >> tmpFile.fileSize)
			{
				m_filesToDL.push_back(tmpFile);
			}
			else
			{
				break;
			}
		}
		return true;
	}
	return false;
}

/*bool Client::checkPresentFiles()
{
	for (int i = 0; i < m_filesToDL.size(); i++)
	{

	}
}*/