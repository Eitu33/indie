/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ServerTournament
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "ServerTournament.hpp"

ServerTournament::ServerTournament(std::string portMainServer, int id)
	: _portMainServer(portMainServer), _id(id)
{
	int i = 0;
	_toMainServer.connectServer(std::stoi(_portMainServer), _ipMainServer);
	for (int i = 0; i < MAX_PLAYERS; i++)
			_clients[i] = std::make_shared<Client>(ClientState::PERSON);
	for (int i = 0; i < MAX_MATCHS; i++)
			_matchs[i] = std::make_shared<Match>(i + 1);
	_manager.init(0);
	unsigned int port = _manager.getPort();
	_toMainServer.sendPacket(std::string("I'm tournament " + std::to_string(_id)) + ":" + std::to_string(port));
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

static int nbMatchs(std::shared_ptr<Match> *matchs)
{
	int nb = 0;

	for (int i = 0; i < MAX_MATCHS; i++) {
		if (matchs[i]->getSocket() != INVALID_SOCKET)
			nb += 1;
	}
	return (nb);
}

void ServerTournament::createMatchs(int nbMatchs)
{
	for (int i = 0; i < nbMatchs; i++) {
#ifdef __linux__
		if (fork() == 0) {
			std::string portTournament = std::to_string(_manager.getPort());
			std::string prevMatchID = std::to_string(_prevMatchID);
			char * const args[4] = {"./server_match", const_cast<char*>(portTournament.c_str()),
			const_cast<char*>(prevMatchID.c_str()), NULL};
			execvp("./server_match", args);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
#endif
#ifdef _WIN64
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		std::string cmd("server_match.exe ");
		cmd.append(std::to_string(_manager.getPort()).c_str());
		cmd.append(" ");
		cmd.append(std::to_string(_prevMatchID).c_str());
		if (!CreateProcess(NULL, strdup(cmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
			std::cout << "Failed created process" << std::endl;
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			exit(84);
		}
#endif
		_prevMatchID = _prevMatchID + 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}

void ServerTournament::connectAllPlayers(void)
{
	int nbPlayer = 0;

	for (int i = 0; i < _lastNbMatch; i++) {
		for (int j = 0; j < 4;) {
			if (_clients[nbPlayer]->getID() != INVALID_SOCKET) {
				_manager.sendPacket(_clients[nbPlayer]->getID(), std::string("Port:") + std::to_string(_matchs[i]->getPort()));
				j++;
			}
			nbPlayer += 1;
		}
		_matchs[i]->setState(MatchState::IN_GAME);
	}
	_lastNbMatch = _lastNbMatch / 2;
}

void ServerTournament::connectNewMatch(SOCKET socket, int id, int port)
{
	for(int i = 0; i < MAX_MATCHS; i++) {
		if (_matchs[i]->getID() == id) {
			_matchs[i]->setSocket(socket);
			_matchs[i]->setPort(port);
		}
	}
}

void ServerTournament::addNewMatch(void)
{
	char *buffer = static_cast<char*>(malloc(sizeof(char) * 1000));
	for (int i = 0; i < MAX_MATCHS; i++) {
		if (_matchs[i]->getSocket() == INVALID_SOCKET) {
			SOCKET socket = _manager.acceptNewConnection();
			_matchs[i]->setSocket(socket);
			int readedbytes = _manager.receivePacket(_matchs[i]->getSocket(), &buffer);
			if (readedbytes > 0) {
				std::string packetContent(buffer);
				connectNewMatch(socket,
				std::stoi(packetContent.substr(10, packetContent.find(':'))),
				std::stoi(packetContent.substr(packetContent.find(':') + 1, packetContent.length())));
			}
			break;
		}
	}
}

void ServerTournament::run(void)
{
	while (true) {
		auto now = std::chrono::system_clock::now();
		std::cout << "Tournament created with " << nbConnected(_clients) << " clients!" << std::endl;
		if(std::chrono::duration_cast<std::chrono::seconds>(now-_started).count() == 3 && _state == TournamentState::WAITING_TIMER) {
			_toMainServer.sendPacket(std::string("Launch the game " + std::to_string(_id)));
			_state = TournamentState::WAITING_FOR_PLAYERS;
		} else if (_state == TournamentState::WAITING_FOR_PLAYERS) {
			if (_manager.manageClients(_clients, MAX_PLAYERS) == 1) {
				for (int i = 0; i < MAX_PLAYERS; i++) {
					if (_clients[i]->getID() == INVALID_SOCKET) {
						_clients[i]->setID(_manager.acceptNewConnection());
						break;
					}
				}
			}
		} else if (_state == TournamentState::WAITING_FOR_MATCHS)
			if (_manager.manageMatchs(_matchs, _lastNbMatch) == 1)
				addNewMatch();
		if (_lastNbMatch * 4 == nbConnected(_clients) && _state == TournamentState::WAITING_FOR_PLAYERS) {
			_state = TournamentState::WAITING_FOR_MATCHS;
			createMatchs(_lastNbMatch);
		}
		if (nbMatchs(_matchs) == _lastNbMatch && _state == TournamentState::WAITING_FOR_MATCHS) {
			connectAllPlayers();
			_state = TournamentState::IN_MATCH;
		}
		if (_state == TournamentState::IN_MATCH) {
			for (int i = 0; i < MAX_PLAYERS; i++) {
				if (_clients[i]->getID() != INVALID_SOCKET) {
					char *buffer = static_cast<char*>(malloc(sizeof(char) * 1000));
					int readedBytes = _manager.receivePacket(_clients[i]->getID(), &buffer);
					if (readedBytes > 0) {
						if (!std::string(buffer).compare(0, 4, "Lost")) {
							closesocket(_clients[i]->getID());
							_clients[i]->setID(INVALID_SOCKET);
						}
					}
				}
			}
		}
		if (_state == TournamentState::IN_MATCH && _lastNbMatch * 4 == nbConnected(_clients)) {
			_prevMatchID = 1;
			for (int i = 0; i < MAX_MATCHS; i++) {
				_matchs[i]->disconnect();
				_matchs[i] = std::make_shared<Match>(i + 1);
			}
			_state = TournamentState::WAITING_FOR_PLAYERS;
			_nbRound += 1;
		}
		if (_state == TournamentState::IN_MATCH && nbConnected(_clients) == 2) {
			for (int i = 0; i < MAX_PLAYERS; i++) {
				if (_clients[i]->getID() != INVALID_SOCKET) {
					_manager.sendPacket(_clients[i]->getID(), std::string("Won Tournament"));
					_manager.closeClient(_clients[i]->getID());
				}
			}
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

ServerTournament::~ServerTournament()
{
}
