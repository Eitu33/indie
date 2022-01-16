/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#ifdef __linux__
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>
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

enum class ClientState {
	IA,
	PERSON
};

class Client {
	public:
		Client(ClientState state);
		~Client();
		SOCKET getID() const
		{
			return (_id);
		}
		void setID(SOCKET id)
		{
			_id = id;
		}
	protected:
	private:
		SOCKET _id = INVALID_SOCKET;
		ClientState _state;
};

#endif /* !CLIENT_HPP_ */
