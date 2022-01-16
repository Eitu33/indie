/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ServerMatch
*/

#ifndef SERVERMATCH_HPP_
#define SERVERMATCH_HPP_

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "Game.hpp"

const int MAX_PLAYERS = 4;

class ServerMatch {
	public:
		ServerMatch(unsigned int portTournamentServer, int id);
		~ServerMatch();
		void MatchLoop(void);
		void run(void);
	protected:
	private:
		unsigned int _portTournamentServer;
		std::string _ipTournamentServer = std::string("127.0.0.1");
		int _id;
		ServerSocket _manager;
		ClientSocket _toTournamentServer;
		std::shared_ptr<Client> _clients[MAX_PLAYERS];
		MatchState _state = MatchState::WAITING_PLAYER_CONNECTION;
		std::shared_ptr<game_logic::Game> _gameLogic;
};

#endif /* !SERVERMATCH_HPP_ */
