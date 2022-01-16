/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ServerTournament
*/

#ifndef SERVERTOURNAMENT_HPP_
#define SERVERTOURNAMENT_HPP_
#include <string>
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "Match.hpp"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
const int MAX_PLAYERS = 32;
const int MAX_MATCHS = 8;

enum class TournamentState {
	WAITING_TIMER,
	WAITING_FOR_PLAYERS,
	WAITING_FOR_MATCHS,
	IN_MATCH
};

class ServerTournament {
	public:
		ServerTournament(std::string portMainServer, int id);
		void run(void);
		void createMatchs(int nbMatches);
		void connectAllPlayers(void);
		void connectNewMatch(SOCKET socket, int id, int port);
		void addNewMatch(void);
		~ServerTournament();
	protected:
	private:
		std::string _ipMainServer = std::string("127.0.0.1");
		int _id;
		std::string _portMainServer;
		ServerSocket _manager;
		ClientSocket _toMainServer;
		std::chrono::time_point<std::chrono::system_clock> _started = std::chrono::system_clock::now();
		TournamentState _state = TournamentState::WAITING_TIMER;
		std::shared_ptr<Client> _clients[MAX_PLAYERS];
		std::shared_ptr<Match> _matchs[MAX_MATCHS] = {};
		std::vector<SOCKET> _tempMatch;
		int _prevMatchID = 1;
		int _nbRound = 1;
		int _lastNbMatch = MAX_MATCHS;
};

#endif /* !SERVERTOURNAMENT_HPP_ */
