/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <exception>
#include <memory>
#include "Tournament.hpp"
#include "ServerSocket.hpp"

class Server {
	public:
		Server(int port);
 		void run(void);
		void newClient(SOCKET nb);
		void newTournamentConnect(SOCKET nb, int id, unsigned short port);
		std::shared_ptr<Tournament> findTournamentByID(int id);
		~Server();
		void addInTournament(std::shared_ptr<Client> &client);
		std::shared_ptr<Tournament> findWaitingTournament();
		std::shared_ptr<Tournament> createNewTournament();
		void statusTournament();
		void newConnection(void);
		void manageWaitingConnections(void);
		void manageClients(void);
		void manageTournaments(void);
	private:
		std::shared_ptr<Client> _clients[MAX_FD];
		SOCKET _connections[MAX_WAITING_CONNECTION];
		bool _serverRunning;
		std::vector<std::shared_ptr<Tournament>> _tournament = {};
		ServerSocket _ServerSocket;
		SOCKET _tournamentPrevID = 1;
};

#endif /* !SERVER_HPP_ */
