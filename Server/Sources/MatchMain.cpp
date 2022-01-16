/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MatchMain
*/

#include <iostream>
#include <string>
#include "ServerMatch.hpp"

int main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << "USAGE: ./server_match [PORTTOURNAMENT] [IDMATCH]" << std::endl;
		exit(84);
	}
	std::string ipPort(av[1]);
	ServerMatch server(std::stoi(ipPort), std::stoi(av[2]));
	server.run();
}