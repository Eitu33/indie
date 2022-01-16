/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Match
*/

#ifndef MATCH_HPP_
#define MATCH_HPP_

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

#include <vector>
#include "Client.hpp"

enum class MatchState {
	WAITING_PLAYER_CONNECTION,
	IN_GAME
};

class Match {
	public:
		Match(int id)
		{
			_id = id;
		};
		~Match();
		MatchState getState(void) const;
		void addPlayer(std::shared_ptr<Client> &client);
		void status(void);
		void disconnect(void)
		{
			_sockFd = INVALID_SOCKET;
			closesocket(_sockFd);
		}
		SOCKET getSocket(void)
		{
			return (_sockFd);
		}
		bool getConnected(void) const
		{
			return (_connected);
		}
		void setSocket(SOCKET nb)
		{
			_connected = true;
			_sockFd = nb;

		}
		int getID(void) const
		{
			return (_id);
		};

		bool operator==(const Match& lhs)
		{
			_id = lhs.getID();
		}
		void setPort(unsigned int port)
		{
			_port = port;
		}
		unsigned short getPort(void)
		{
			return (_port);
		}
		void setState(MatchState state)
		{
			_state = state;
		}
	private:
		int _id;
		SOCKET _sockFd = INVALID_SOCKET;
		bool _connected = false;
		MatchState _state = MatchState::WAITING_PLAYER_CONNECTION;
		std::vector<std::shared_ptr<Client>> _clients;
		unsigned short _port;
};

#endif /* !MATCH_HPP_ */
