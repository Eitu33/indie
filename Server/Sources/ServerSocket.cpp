/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ServerSocket
*/

#include <iostream>
#include "ServerSocket.hpp"

static const int PACKET_SIZE = 100000;

ServerSocket::ServerSocket()
{
}

void ServerSocket::init(unsigned short port)
{
#if _WIN64
	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);
#endif
	_socketMaster = socket(AF_INET, SOCK_STREAM, 0); // so_reusable
#if _WIN64
	unsigned long l = 1;
	ioctlsocket(_socketMaster, FIONBIO, &l);
#endif
	if (_socketMaster == 0)
		throw ServerError("Constructor Server", "Failed to create socket");
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(port);
	if (bind(_socketMaster, (struct sockaddr *)&_address, sizeof(_address)) < 0)
		throw ServerError("Constructor Server", "Bind error");
	if (listen(_socketMaster, MAX_FD) < 0)
		throw ServerError("Constructor Server", "Listen error");
	_port = std::stoi(serialize());
}

SOCKET ServerSocket::acceptNewConnection()
{
#ifdef _WIN64
	int addrlen = sizeof(_address);
#endif
#ifdef __linux__
	unsigned int addrlen = sizeof(_address);
#endif
	return (accept(_socketMaster,
		       (struct sockaddr *)&_address, &addrlen));
}

std::string ServerSocket::serialize()
{
	std::string serialized;
	SOCKADDR_IN sin;
#ifdef __linux__
	socklen_t len = sizeof(sin);
#endif
#ifdef _WIN64
	int len = sizeof(sin);
#endif
	getsockname(_socketMaster, (SOCKADDR *)&sin, &len);
	return (std::to_string(ntohs(sin.sin_port)));
}

int ServerSocket::receivePacket(SOCKET socketClient, char **buffer)
{
#ifdef __linux__
	size_t size = PACKET_SIZE;
	return (recv(socketClient, *buffer, size, MSG_DONTWAIT));
#endif
#ifdef _WIN64
	int size = PACKET_SIZE;
	for (int i = 0; i < PACKET_SIZE; i++)
		(*buffer)[i] = '\0';
	return (recv(socketClient, *buffer, size, 0));
#endif
}

int ServerSocket::sendPacket(SOCKET socketClient, std::string buffer)
{
	return (send(socketClient, buffer.c_str(), buffer.length(), 0));
}

void ServerSocket::closeClient(SOCKET socketClient)
{
	closesocket(socketClient);
}

int ServerSocket::manageMatchs(std::shared_ptr<Match> *matchs, int maxMatchs)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 500000;
	FD_ZERO(&_allFds);
	FD_SET(_socketMaster, &_allFds);
#ifdef __linux__
	int fd = 0;
	int maxFd = 0;
	maxFd = _socketMaster;
	for (int i = 0; i < maxMatchs; i++)
	{
		fd = matchs[i]->getID();
		if (fd > 0)
			FD_SET(fd, &_allFds);
		if (fd > maxFd)
			maxFd = fd;
	}
	select(maxFd + 1, &_allFds, NULL, NULL, &timeout);
#endif
#ifdef _WIN64
	for (int i = 0; i < maxMatchs; i++)
	{
		SOCKET fd = matchs[i]->getID();
		if (fd != INVALID_SOCKET)
			FD_SET(fd, &_allFds);
	}
	select(_socketMaster + 1, &_allFds, NULL, NULL, &timeout);
#endif
	timeout.tv_sec = 0;
	timeout.tv_usec = 500000;
	if (FD_ISSET(_socketMaster, &_allFds))
	{
		return (1);
	}
}

int ServerSocket::manageClients(std::shared_ptr<Client> *clients, int maxClients)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 500000;
	FD_ZERO(&_allFds);
	FD_SET(_socketMaster, &_allFds);
#ifdef __linux__
	int fd = 0;
	int maxFd = 0;
	maxFd = _socketMaster;
	for (int i = 0; i < maxClients; i++)
	{
		fd = clients[i]->getID();
		if (fd > 0)
			FD_SET(fd, &_allFds);
		if (fd > maxFd)
			maxFd = fd;
	}
	select(maxFd + 1, &_allFds, NULL, NULL, &timeout);
#endif
#ifdef _WIN64
	for (int i = 0; i < maxClients; i++)
	{
		SOCKET fd = clients[i]->getID();
		if (fd != INVALID_SOCKET)
			FD_SET(fd, &_allFds);
	}
	select(_socketMaster + 1, &_allFds, NULL, NULL, &timeout);
#endif
	timeout.tv_sec = 0;
	timeout.tv_usec = 500000;
	if (FD_ISSET(_socketMaster, &_allFds))
	{
		return (1);
	}
}

ServerSocket::~ServerSocket()
{
}
