/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ClientSocket
*/

#include <iostream>
#include "ClientSocket.hpp"

static const int PACKET_SIZE = 100000;

ClientSocket::ClientSocket()
{
}

void ClientSocket::connectServer(unsigned short port, std::string ip)
{
	#ifdef __linux__
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	_servAddress.sin_family = AF_INET;
	_servAddress.sin_port = htons(port);

	if (inet_pton(AF_INET, ip.c_str(), &_servAddress.sin_addr) <= 0)
		ServerError("Connect server", "\nInvalid address/ Address not supported \n");
#endif
#ifdef _WIN64
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,0), &WSAData);
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	_servAddress.sin_addr.s_addr = inet_addr(ip.c_str());
	_servAddress.sin_family = AF_INET;
	_servAddress.sin_port = htons(port);
#endif
	if (connect(_socket, (struct sockaddr *)&_servAddress, sizeof(_servAddress)) < 0)
		ServerError("Connect server", "\nConnection Failed \n");
#ifdef _WIN64
	unsigned long l = 1;
	ioctlsocket(_socket, FIONBIO, &l);
#endif
}

int ClientSocket::receivePacket(char **buffer)
{
	#ifdef __linux__
	size_t size = PACKET_SIZE;
	return (recv(_socket, *buffer, size, MSG_DONTWAIT));
#endif
#ifdef _WIN64
	int size = PACKET_SIZE;
	for (int i = 0; i < PACKET_SIZE; i++)
		(*buffer)[i] = '\0';
	return (recv(_socket, *buffer, size, 0));
#endif
}

int ClientSocket::sendPacket(std::string buffer) const
{
	return (send(_socket, buffer.c_str(), buffer.length(), 0));
}

void ClientSocket::disconnectServer(void)
{
	closesocket(_socket);
}

ClientSocket::~ClientSocket()
{
}
