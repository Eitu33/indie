/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Tournament
*/

#ifndef TOURNAMENT_HPP_
#define TOURNAMENT_HPP_
#include <memory>
#include <vector>
#include "Client.hpp"
#include "ServerErrors.hpp"
#include "ServerSocket.hpp"

enum class TournamentState {
	WAITING_TIMER,
	STARTED
};

static const int NB_CLIENT = 32;
class Tournament {
	public:
		Tournament(int id)
		{
			_id = id;
		};
		~Tournament();
		TournamentState getState(void) const;
		void start(std::string);
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

		bool operator==(const Tournament& lhs)
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
		void connectAllPlayers(ServerSocket _socketServer);
	private:
		int _id;
		SOCKET _sockFd = INVALID_SOCKET;
		bool _connected = false;
		TournamentState _state = TournamentState::WAITING_TIMER;
		std::vector<std::shared_ptr<Client>> _clients;
		unsigned short _port;
		
};

#endif /* !TOURNAMENT_HPP_ */
