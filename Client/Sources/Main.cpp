/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Main
*/

#include <iostream>
#include "Client.hpp"

int main(int ac, char **av)
{
	if (ac == 1) {
		Client client(PERSON, port);
		client.run();
	} else {
		Client client(IA, std::stoi(av[2]));
		client.run();
	}
}