/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Match
*/

#include <iostream>
#include <string.h>
#include <thread>
#include <chrono>
#include "Match.hpp"
#include "ServerSocket.hpp"

MatchState Match::getState(void) const
{
	return (_state);
}

void Match::status(void)
{
	std::cout << "Match id: " << _id << std::endl;
	std::cout << "Connected: " << _connected << std::endl;
	std::cout << "There is actually " << _clients.size() << " clients." << std::endl;
}

void Match::addPlayer(std::shared_ptr<Client> &client)
{
	_clients.push_back(client);
}

Match::~Match()
{
}