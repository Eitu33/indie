/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MapGeneration
*/

#ifndef MAPGENERATION_HPP_
#define MAPGENERATION_HPP_

#include <string>
#include <vector>

class MapGeneration {
	public:
		MapGeneration(const int &height = 100, const int &width = 100);
		~MapGeneration() = default;

		void generateMap();
		void generateMap(const int &height, const int &width); //generate a new map

		std::vector<std::pair<float, float>> getPosByChar(const char &toGet, const int &tileSize = 30); //to get differents elements of the map

		std::vector<std::string> getMap() const {return _map;};	

		char indestructible = 'X';
		char destructible = 'D';
		char road = ' ';
		char player = 'P';

	private:
		void fillIndestructible();	//just fill the map with obstacle
		void fillDestructible();	//replace some ostacle by desctructible ones
		void fillPlayer();		//put 4 players in the corners
		void fillRoad();		//replace some obstacle with road
		void addDestructible();		//add some destructibles on the road to hide it a bit
		void addBorders();		//add borders

		std::vector<std::string> _map;
		int _height;
		int _width;
};

#endif /* !MAPGENERATION_HPP_ */