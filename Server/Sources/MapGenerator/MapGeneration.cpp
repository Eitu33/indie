/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MapGeneration
*/

#include <iostream>

#include <cstdlib>
#include <ctime>

#include "MapGeneration.hpp"

MapGeneration::MapGeneration(const int &height, const int &width)
	: _height(height), _width(width)
{
	std::srand(std::time(nullptr));
}

void MapGeneration::generateMap()
{
	fillIndestructible();
	fillDestructible();
	fillPlayer();
	fillRoad();
	addDestructible();
	fillPlayer();
	addBorders();
}

void MapGeneration::generateMap(const int &height, const int &width)
{
	_height = height;
	_width = width;

	generateMap();
}

void MapGeneration::fillIndestructible()
{
	std::string line;

	for (auto i = 0; i < _width; i++)		//create the line to fill the map
		line.push_back(indestructible);

	for (auto i = 0; i < _height; i++)		//fill each line of the map
		_map.push_back(line);

}

void MapGeneration::fillDestructible()
{
	std::string line;

	for (auto i = 0; i < _width; i++)		//create the line to fill the map
		line.push_back(destructible);

	for (auto i = 0; i < 1 + _height / 2; i++) {			//fill random lines of the map
		int posY = std::rand() / ((RAND_MAX + 1u) / _height);
		_map[posY].replace(0, _width, line);
	}

	for (auto i = 0; i < 1 + _width / 2; i++) {			//fill random columns of the map
		int posX = std::rand() / ((RAND_MAX + 1u) / _width);
		for (auto j = 0; j < _height; j++)
			_map[j][posX] = destructible;
	}
}

void MapGeneration::fillRoad()
{
	int x = 0;
	int y = 0;

	while (1) {
		if (x >= _height - 1) {
			for (auto j = y; _map[x][j] != player; j++)
				_map[x][j] = road;
			break;
		}

		if (y >= _width - 1) {
			for (auto j = x; _map[j][y] != player; j++)
				_map[j][y] = road;
			break;
		}

		if (_map[x + 1][y] == indestructible) {
			if (_map[x][y + 1] == indestructible) {
				int rand = std::rand() / ((RAND_MAX + 1u) / 2);
				if (!rand)
					++y;
				else
					++x;
				_map[x][y] = road;
				continue;
			}
			_map[++x][y] = road;
			continue;
		}

		if (_map[x][y + 1] == indestructible) {
			_map[x][++y] = road;
			continue;
		}


		int rand = std::rand() / ((RAND_MAX + 1u) / 2);
		if (!rand)
			++y;
		else
			++x;
		_map[x][y] = road;
	}

	x = 0;
	y = _width - 1;

	while (1) {
		if (x >= _height - 1) {
			for (auto j = y; _map[x][j] != player; j--)
				_map[x][j] = road;
			break;
		}

		if (y <= 0) {
			for (auto j = x; _map[j][y] != player; j++)
				_map[j][y] = road;
			break;
		}

		if (_map[x + 1][y] == indestructible) {
			if (_map[x][y - 1] == indestructible) {
				int rand = std::rand() / ((RAND_MAX + 1u) / 2);
				if (!rand)
					y--;
				else
					x++;
				_map[x][y] = road;
				continue;
			}
			_map[++x][y] = road;
			continue;
		}

		if (_map[x][y - 1] == indestructible) {
			_map[x][--y] = road;
			continue;
		}


		int rand = std::rand() / ((RAND_MAX + 1u) / 2);
		if (!rand)
			y--;
		else
			x++;
		_map[x][y] = road;
	}
}

void MapGeneration::addDestructible()
{
	for (auto &elem : _map) {
		for (auto j = 0; j < _width; j++) {
			if (elem[j] == road) {
				int rand = std::rand() / ((RAND_MAX + 1u) / 5);
				if (rand)
					elem[j] = destructible;
			}
		}
	}
}

void MapGeneration::fillPlayer()
{
	_map[0][0] = player;
	_map[0][_width - 1] = player;
	_map[_height - 1][0] = player;
	_map[_height - 1][_width - 1] = player;
}

void MapGeneration::addBorders()
{
	//player one lifesapce
	_map[0][1] = road;
	_map[1][0] = road;
	//player two lifesapce
	_map[0][_width - 2] = road;
	_map[1][_width - 1] = road;
	//player three lifesapce
	_map[_height - 2][0] = road;
	_map[_height - 1][1] = road;
	//player four lifesapce
	_map[_height - 2][_width - 1] = road;
	_map[_height - 1][_width - 2] = road;
	
	std::string line;

	for (auto i = 0; i < _width + 2; i++)		//create the line to fill the map
		line.push_back(indestructible);

	_map.push_back(line);
	_map.insert(_map.begin(), line);
	
	for (auto i = 1; i < _height + 1; i++) {
		_map[i].push_back(indestructible);
		_map[i].insert(_map[i].begin(), indestructible);
	}
}

std::vector<std::pair<float, float>> MapGeneration::getPosByChar(const char &toGet, const int &tileSize)
{
	std::vector<std::pair<float, float>> pos;

	for (auto i = 0; i < _map.size(); i++)
		for (auto j = 0; j < _map[i].size(); j++)
			if (_map[i][j] == toGet)
				pos.push_back(std::pair<float, float>(j * tileSize, i * tileSize));
	
	return pos;
}