/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Main
*/

#include <iostream>
#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "USAGE: ./server [port]" << std::endl;
		exit(84);
	}
	Server server(std::stoi(av[1]));
	//Server server(4343);
	server.run();
}