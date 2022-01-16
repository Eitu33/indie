/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "Client.hpp"
#include "EventKeyEnum.hpp"

static const int PACKET_SIZE = 100000;

Client::Client(ClientType type, unsigned int portServer)
{
	_type = type;
	if (_type == PERSON) {
		_toMainServer.connectServer(portServer, std::string(ipServer));
		_toMainServer.sendPacket(std::string("I'm client!"));
	} else {
		_toTournament.connectServer(portServer, std::string(ipServer));
		_state = ClientState::CONNECTED_TO_TOURNAMENT;
	}
	_manageReponseFunctions[0] = &Client::manageReponseMainServer;
	_manageReponseFunctions[1] = &Client::manageReponseMainServer;
	_manageReponseFunctions[2] = &Client::manageReponseInTournament;
	_manageReponseFunctions[3] = &Client::manageReponseInGame;
}

void Client::manageReponseMainServer(std::string reponse)
{
	if (!reponse.compare("Connected")) {
		setState(ClientState::WAITING_FOR_LAUNCH);
		_sceneState = SceneFromClientState::WAITING_FOR_LAUNCH;
	} else if (!reponse.compare(0, 5, "Port:") && _state == ClientState::WAITING_FOR_LAUNCH) {
		unsigned short portTournament = std::stoi(reponse.substr(reponse.find(':') + 1, reponse.length()));
		std::cout << "port tournament = " << portTournament << std::endl;
		_toTournament.connectServer(portTournament, ipServer);
		_state = ClientState::CONNECTED_TO_TOURNAMENT;
	}
}

void Client::manageReponseInTournament(std::string reponse)
{
	if (!reponse.compare(0, 5, "Port:")) {
		unsigned short portMatch = std::stoi(reponse.substr(reponse.find(':') + 1, reponse.length()));
		_toMatch.connectServer(portMatch, ipServer);
		_state = ClientState::IN_GAME;
		_sceneState = SceneFromClientState::IN_GAME;
	} else if (!reponse.compare(0, 14, "Won Tournament")) {
		std::cout << "I WONNNNNNNNN!" << std::endl;
		_sceneState = SceneFromClientState::WIN;
		_toTournament.disconnectServer();
	}
}

void Client::manageReponseInGame(std::string reponse)
{
	if (!reponse.compare(0, 3, "Won")) {
		_toTournament.sendPacket(std::string("Won"));
		_sceneState = SceneFromClientState::WAITING_FOR_LAUNCH;
		std::cout << "I go to next turn !" << std::endl;
	} else if (!reponse.compare(0, 4, "Lost")) {
		_toTournament.sendPacket(std::string("Lost"));
		_toTournament.disconnectServer();
		std::cout << "I have lost :(" << std::endl;
		_sceneState = SceneFromClientState::LOSE;
		if (_type == ClientType::IA)
			_running = false;
	} else {
		if (_firstRecup) {
			_firstRecup = false;
			_id = std::atoi(reponse.substr(0, reponse.find(':')).c_str());
			reponse = reponse.substr(reponse.find(":") + 1, reponse.length());
			_firstInfoGame = _gameLogic.deserialize(std::string(reponse));
			if (_type == ClientType::IA) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10000));
			}
		}
		_infosInGame = _gameLogic.deserialize(std::string(reponse));
		if (_type == ClientType::IA) {
			std::vector<std::string> commands = _ai.autoPlay(_infosInGame, _id);
			for (auto &elem : commands) {
				_toMatch.sendPacket(elem);
			}
		}
	}
}

void Client::run(void)
{
	while (_running) {
		char *buffer = static_cast<char*>(malloc(sizeof(char) * PACKET_SIZE));
		int readedBytes = _toMainServer.receivePacket(&buffer);
		if (readedBytes == 0) {
			std::cerr << "Server killed" << std::endl;
			exit(0);
		}
		else if (readedBytes > 0) {
			_manageReponseFunctions[static_cast<int>(_state)](this, std::string(buffer));
		}
		if (_state == ClientState::CONNECTED_TO_TOURNAMENT) {
			char *buffer = static_cast<char*>(malloc(sizeof(char) * PACKET_SIZE));
			int readedBytes = _toTournament.receivePacket(&buffer);
			if (readedBytes > 0) {
				_manageReponseFunctions[static_cast<int>(_state)](this, std::string(buffer));
			}
		}
		if (_state == ClientState::IN_GAME) {
			char *buffer = static_cast<char*>(malloc(sizeof(char) * PACKET_SIZE));
			int readedBytes = _toMatch.receivePacket(&buffer);
			if (readedBytes > 0)
				_manageReponseFunctions[static_cast<int>(_state)](this, std::string(buffer));
			else if (readedBytes == 0) {
				_firstTurn = true;
				_toMatch.disconnectServer();
				_state = ClientState::CONNECTED_TO_TOURNAMENT;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

Client::~Client()
{
}
