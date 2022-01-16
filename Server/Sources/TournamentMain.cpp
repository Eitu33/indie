/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** TournamentMain
*/

#include <iostream>
#include "ServerTournament.hpp"

int main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << "USAGE: ./server_tournament [PORTMAIN] [IDTOURNAMENT]" << std::endl;
		exit(84);
	}
	std::string ipPort(av[1]);
	ServerTournament server(ipPort, std::stoi(av[2]));
	server.run();
}