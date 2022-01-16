/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ServerMatch
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "ServerMatch.hpp"
#include "EventKeyEnum.hpp"

static const int PACKET_SIZE = 100000;

ServerMatch::ServerMatch(unsigned int portTournamentServer, int id)
	:	_portTournamentServer(portTournamentServer), _id(id)
{
	int i = 0;

	_toTournamentServer.connectServer(_portTournamentServer, _ipTournamentServer);
	for (int i = 0; i < MAX_PLAYERS; i++) {
			_clients[i] = std::make_shared<Client>(ClientState::PERSON);
	}
	_manager.init(0);
	unsigned int portMatch = _manager.getPort();
	_toTournamentServer.sendPacket(std::string("I'm match " + std::to_string(_id)) + ":" + std::to_string(portMatch));
}

static int nbConnected(std::shared_ptr<Client> *clients)
{
	int nb = 0;

	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (clients[i]->getID() != INVALID_SOCKET)
			nb += 1;
	}
	return (nb);
}

void ServerMatch::MatchLoop(void)
{
	int tmp = true;
	static bool firstTurn = true;
	std::vector<SOCKET> _players;
	std::vector<unsigned int> winners;

	for (auto i = 0; i != MAX_PLAYERS; i++)
		_players.push_back(_clients[i]->getID());
	while(_gameLogic->update()) {
		std::string serializedString = _gameLogic->serialize();
		for (auto it = _players.begin(); it != _players.end(); it++) {
			if (firstTurn)
				serializedString = std::to_string((*it)) + ":" + serializedString;
			_manager.sendPacket((*it), serializedString);
			char *buffer = static_cast<char*>(malloc(sizeof(char) * PACKET_SIZE));
			int readedBytes = _manager.receivePacket((*it), &buffer);
			if (readedBytes > 0) {
				EventType event = static_cast<EventType>(std::atoi(buffer));
				if (event != EventType::PutBomb) {
					_gameLogic->move((*it), static_cast<game_logic::Direction>(event));
				} else {
					_gameLogic->dropBomb((*it));
				}
			}
		}
		firstTurn = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	winners = _gameLogic->getWinnersId();
	_manager.sendPacket(*(winners.end() - 1), std::string("Won"));
	_manager.sendPacket(*(winners.end() - 2), std::string("Won"));
	_manager.sendPacket(*(winners.end() - 3), std::string("Lost"));
	_manager.sendPacket(*(winners.end() - 4), std::string("Lost"));
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	closesocket(*(winners.end() - 1));
	closesocket(*(winners.end() - 2));
	closesocket(*(winners.end() - 3));
	closesocket(*(winners.end() - 4));
}

void ServerMatch::run(void)
{
	std::vector<unsigned int> ids;
	while(true) {
		if (_manager.manageClients(_clients, MAX_PLAYERS) == 1) {
			for (int i = 0; i < MAX_PLAYERS; i++) {
				if (_clients[i]->getID() == INVALID_SOCKET) {
					_clients[i]->setID(_manager.acceptNewConnection());
				}
			}
		}
		if (nbConnected(_clients) == 4) {
			for (auto i = 0; i < MAX_PLAYERS; i++) {
				ids.push_back(_clients[i]->getID());
			}
			_gameLogic = std::make_shared<game_logic::Game>(ids);
			_state = MatchState::IN_GAME;
			MatchLoop();
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

ServerMatch::~ServerMatch()
{
	_toTournamentServer.disconnectServer();
}
