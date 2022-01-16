/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ServerSocket
*/

#ifndef ServerSocket_HPP_
#define ServerSocket_HPP_

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

#ifdef _WIN32
	#include <WinSock2.h>
#endif

#include <memory>
#include "Client.hpp"
#include "ServerErrors.hpp"
#include "Match.hpp"
const int MAX_FD = 1000;

const int MAX_TOURNAMENT = 100;

const int MAX_WAITING_CONNECTION = 200;

class ServerSocket {
	public:
		ServerSocket();
		void init(unsigned short _port);
		int manageClients(std::shared_ptr<Client> *clients, int maxClients);
		int manageMatchs(std::shared_ptr<Match> *matchs, int maxMatchs); 
		SOCKET acceptNewConnection();
		int receivePacket(SOCKET clientFd, char **buffer);
		int sendPacket(SOCKET clientFd, std::string buffer);
		std::string serialize();
		unsigned short getPort() const {
			return _port;
		};
		void closeClient(SOCKET clientFd);
		~ServerSocket();
	protected:
	private:
		unsigned short _port;
		SOCKET _socketMaster;
		fd_set _allFds;
		SOCKADDR_IN _address;
		SOCKADDR_IN _servAddress;
};

#endif /* !ServerSocket_HPP_ */
