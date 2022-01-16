/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Server
*/

#include <iostream>
#include "Server.hpp"
#include "ServerErrors.hpp"
#include <chrono>
#include <thread>

Server::Server(int port)
{
	_ServerSocket.init(port);
	for (int i = 0; i < MAX_FD; i++) {
		    _clients[i] = std::make_shared<Client>(ClientState::PERSON);
	}
	_serverRunning = true;
	for (int i = 0; i < MAX_WAITING_CONNECTION; i++)
		_connections[i] = INVALID_SOCKET;
}

std::shared_ptr<Tournament> Server::findWaitingTournament()
{
	auto it = _tournament.begin();
	for (; it != _tournament.end(); it++) {
		if ((*it)->getState() == TournamentState::WAITING_TIMER)
			return (*it);
	}
	return (createNewTournament());
}

std::shared_ptr<Tournament> Server::createNewTournament()
{
	_tournament.push_back(std::make_shared<Tournament>(Tournament(_tournamentPrevID)));
	_tournamentPrevID += 1;
	_tournament.back()->start(_ServerSocket.serialize());
	return (_tournament.back());
	throw ServerError("Create Tournament", "Too many tournament");
}

void Server::addInTournament(std::shared_ptr<Client> &client)
{
	auto tournament = findWaitingTournament();
	tournament->addPlayer(client);
}

void Server::newClient(SOCKET nb)
{
    	for (int i = 0; i < MAX_FD; i++) {
		if (_clients[i]->getID() == INVALID_SOCKET) {
			_clients[i]->setID(nb);
			addInTournament(_clients[i]);
			_ServerSocket.sendPacket(_clients[i]->getID(), std::string("Connected"));
			break;
		}
	}
}

static int nbConnected(std::shared_ptr<Client> *clients)
{
	int nb = 0;

	for (int i = 0; i < MAX_FD; i++) {
		if (clients[i]->getID() != INVALID_SOCKET)
			nb += 1;
	}
	return (nb);
}

static int nbClientWaiting(SOCKET *connections)
{
	int nb = 0;

	for (int i = 0; i < MAX_WAITING_CONNECTION; i++) {
		if (connections[i] != INVALID_SOCKET)
			nb += 1;
	}
	return (nb);
}

void Server::statusTournament(void)
{
	int i = 0;
	for (auto it = _tournament.begin(); it != _tournament.end(); it++) {
		if ((*it)->getState() == TournamentState::WAITING_TIMER) {
			(*it)->status();
			i++;
		}
	}
	std::cout << "There is " << i << " tournament." << std::endl;
}

void Server::newConnection(void)
{
	for (int i = 0; i < MAX_WAITING_CONNECTION; i++) {
		if (_connections[i] == INVALID_SOCKET) {
			_connections[i] = _ServerSocket.acceptNewConnection();
			break;
		}
	}
}

std::shared_ptr<Tournament> Server::findTournamentByID(int id)
{
	for (auto it = _tournament.begin(); it != _tournament.end(); it++) {
		if ((*it)->getID() == id)
			return (*it);
	}
}

void Server::newTournamentConnect(SOCKET nb, int id, unsigned short port)
{
	std::shared_ptr<Tournament> tournament = findTournamentByID(id);

	tournament->setSocket(nb);
	tournament->setPort(port);
}

void Server::manageWaitingConnections(void)
{
	for (int i = 0; i < MAX_WAITING_CONNECTION; i++) {
		if (_connections[i] != INVALID_SOCKET) {
			char *buffer = static_cast<char*>(malloc(sizeof(char) * 1000));
			int bytesReaded = _ServerSocket.receivePacket(_connections[i], &buffer);
			if (bytesReaded == 0) {
				_ServerSocket.closeClient(_connections[i]);
				_connections[i] = INVALID_SOCKET;
			} else if (bytesReaded > 0) {
				std::string packetContent(buffer);
				if (!packetContent.compare(0, 11, "I'm client!")) {
					newClient(_connections[i]);
					_connections[i] = INVALID_SOCKET;
				} else if (!packetContent.compare(0, 14, "I'm tournament")) {
					newTournamentConnect(_connections[i],
					std::stoi(std::string(packetContent.substr(14, packetContent.find(':')))),
					std::stoi(std::string(packetContent.substr(packetContent.find(':') + 1, packetContent.length()))));
					_connections[i] = INVALID_SOCKET;
				}
			}
		}
	}
}

void Server::manageClients(void)
{
	for (int i = 0; i < MAX_FD; i++) {
		if (_clients[i]->getID() != INVALID_SOCKET) {
			char *buffer = static_cast<char*>(malloc(sizeof(char) * 1000));
			int readedBytes = _ServerSocket.receivePacket(_clients[i]->getID(), &buffer);
			if (readedBytes == 0) {
				_ServerSocket.closeClient(_clients[i]->getID());
				_clients[i]->setID(INVALID_SOCKET);
				break;
			 } else if (readedBytes > 0) {
				std::string packetContent(buffer);
			 }
		}
	}
}

void Server::manageTournaments(void)
{
	for (auto it = _tournament.begin(); it != _tournament.end(); it++) {
		if ((*it)->getConnected()) {
			char *buffer = static_cast<char*>(malloc(sizeof(char) * 1000));
			int readedbytes = _ServerSocket.receivePacket((*it)->getSocket(), &buffer);
			if (readedbytes == 0) {
				(*it)->disconnect();
				break;
			} else if (readedbytes > 0) {
				std::string packetContent(buffer);
				if (!packetContent.compare(0, 16, "Launch the game ")) {
					int idTournament = std::stoi(std::string(packetContent.substr(16, packetContent.length())));
					(*it)->connectAllPlayers(_ServerSocket);
				}
			}
		}
	}
}

void Server::run(void)
{
	int maxFd = 0;
	int fd = 0;

	while (_serverRunning) {
		if (_ServerSocket.manageClients(_clients, MAX_FD) == 1) {
			try {
				newConnection();
			} catch (ServerError &error) {
				std::cerr << error.where() << ": " << error.what() << std::endl;
				_serverRunning = false;
				exit(84);
			}
		}
		manageWaitingConnections();
		manageClients();
		manageTournaments();
		if(std::cin.eof()) {
			exit(0);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

Server::~Server()
{
}