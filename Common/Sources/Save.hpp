/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Save
*/

#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <string>
#include <iostream>
#include <fstream>

class Save {
	public:
		Save() = default;
		~Save() = default;

		static void saveGame(const std::string &gameWalls)
		{
			std::ofstream ofs;
			ofs.open("../media/Saves/save.txt", std::ofstream::out | std::ofstream::trunc);
			ofs <<gameWalls <<std::endl;
			ofs.close();
		};

		static const std::string loadGame()
		{
			std::ifstream myReadFile;
			myReadFile.open("../media/Saves/save.txt");
			std::string ret;

			if (myReadFile.is_open()) {
				myReadFile >> ret;
			}

			myReadFile.close();
			return ret;
		};

	protected:
	private:
};

#endif /* !SAVE_HPP_ */