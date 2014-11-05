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
	/*for (int i = 0; i < (int)line.length(); i++)
	{
		if (line[i] == '-')
		{
			i++;
			if (line[i] == 'h')
			{
				m_fileLog.log("host finded : ");
				i++;
				
				std::string tmpIp;
				for (i; i < (int)line.length(); i++)
				{
					if (line[i] == ' ')
					{
						m_fileLog.log("break : " + std::to_string(i));
						break;
					}
					tmpIp += line[i];
					m_fileLog.log("adding : " + line[i]);
				}
				m_fileLog.log(tmpIp);
				m_sampServerIp = tmpIp;
			
			}

			if (line[i] == 'p')
			{
				m_fileLog.log("port finded");
				i++;
				std::string tmpPort;
				for (i; i < (int)line.length(); i++)
				{
					if (line[i] == ' ')
					{
						break;
					}
					tmpPort += line[i];
				}
				m_fileLog.log(tmpPort);
				if (Utils::from_string<unsigned short>(m_sampServerPort, tmpPort, std::dec))
				{
					return false;
				}
			}
		}
	}*/



	m_fileLog.log("Ip : " + m_sampServerIp.toString() + " Port : " + std::to_string(m_sampServerPort));
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