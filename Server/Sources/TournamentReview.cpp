/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Tournament
*/

#include <iostream>
#include <string.h>
#include <thread>
#include <chrono>
#include "Tournament.hpp"

TournamentState Tournament::getState(void) const
{
	return (_state);
}

void Tournament::connectAllPlayers(ServerSocket _serverSocket)
{
	int nbClient = _clients.size();

	for (int i = nbClient; i != NB_CLIENT; i++) {
		_clients.push_back(std::make_shared<Client>(Client(ClientState::IA)));
		#ifdef __linux__
		if (fork() == 0) {
			char *args[4] = {(char *)"./ia_review", (char *)"IA", const_cast<char*>(std::to_string(_port).c_str()), NULL};
			execvp("./ia_review", args);
		}
		#endif
		#ifdef _WIN64
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		std::string cmd("ia_review.exe ");
		cmd.append("IA");
		cmd.append(" ");
		cmd.append(strdup(std::to_string(_port).c_str()));
		if (!CreateProcess(NULL, strdup(cmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
			std::cout << "Failed created process" << std::endl;
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		#endif
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	if (_connected == false)
		throw ServerError("Tournament", "Server tournament is disconnected!");
	for (auto it = _clients.begin(); it != _clients.end(); it++) {
		_serverSocket.sendPacket((*it)->getID(), std::string("Port:") + std::to_string(_port));
	}
}

void Tournament::status(void)
{
	std::cout << "Tournament id: " << _id << std::endl;
	std::cout << "Connected: " << _connected << std::endl;
	std::cout << "There is actually " << _clients.size() << " clients." << std::endl;
}

void Tournament::start(std::string port)
{
	_state = TournamentState::WAITING_TIMER;
	#ifdef __linux__
	if (fork() == 0) {
		char *args[4] = {(char *)"./server_tournament", strdup(port.c_str()), strdup(std::to_string(_id).c_str()), NULL};
		execvp((char *)"./server_tournament", args);
	}
	#endif
	#ifdef _WIN64
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	std::string cmd("server_tournament.exe ");
	cmd.append(port.c_str());
	cmd.append(" ");
	cmd.append(std::to_string(_id).c_str());
	if (!CreateProcess(NULL, strdup(cmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		std::cout << "Failed created process" << std::endl;
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		exit(84);
	}
	#endif
}

void Tournament::addPlayer(std::shared_ptr<Client> &client)
{
	_clients.push_back(client);
}

Tournament::~Tournament()
{
}