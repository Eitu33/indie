/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ClientSocket
*/

#ifndef ClientSocket_HPP_
#define ClientSocket_HPP_

#ifdef __linux__
	#include <sys/socket.h> 
	#include <netinet/in.h> 
	#include <sys/time.h>
	#include <limits.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(s) close(s)
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#endif

#ifdef _WIN64
	#include <WinSock2.h>
#endif

#include <string>
#include "ServerErrors.hpp"

class ClientSocket {
	public:
		ClientSocket();
		~ClientSocket();
		void connectServer(unsigned short port, std::string ip);
		void disconnectServer(void);
		int receivePacket(char **buffer);
		int sendPacket(std::string buffer) const;
	protected:
	private:
		SOCKADDR_IN _servAddress;
		SOCKET _socket;
};

#endif /* !ClientSocket_HPP_ */
