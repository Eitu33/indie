/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Ai
*/

#include <thread>
#include <iostream>
#include <vector>

#include "EventKeyEnum.hpp"
#include "Ai.hpp"

int abs(int toabs)
{
	return (toabs < 0) ? -toabs : toabs;
}

std::vector<std::string> Ai::autoPlay(const game_logic::GameData &infos, const int &id) 
{
	std::vector<std::string> commands;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	for (auto &players : infos.players) {
		if (id == players.id) {
			if (_aiBomb == 0) {
				for (auto &walls : infos.walls) {
					if (!walls.isTough) {
						if (abs(walls.x - players.x) < abs(_aix - players.x) && abs(walls.y - players.y) < abs(_aiy - players.y)) {
							_aix = walls.x;
							_aiy = walls.y;
						}
					}
				}
				if (_aix > players.x) {
					for (size_t time = 0; time < 20; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveLeft)));
					_wayx = 0;
				}
				if (_aix < players.x) {
					for (size_t time = 0; time < 20; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveRight)));
					_wayx = 1;
				}
				if (_aiy > players.y) {
					for (size_t time = 0; time < 20; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveDown)));
					_wayy = 0;
				}
				if (_aiy < players.y) {
					for (size_t time = 0; time < 20; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveUp)));
					_wayy = 1;
				}
				if (_aix == players.x)
					for (size_t time = 0; time < 10; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveRight)));
				if (_aiy == players.y)
					for (size_t time = 0; time < 10; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveUp)));
				if (abs(_aix - players.x) < 75 && abs(_aiy - players.y) < 75)
					_aiBomb = 1;
			}
			else if (_aiBomb == 1)
			{
				commands.push_back(std::to_string(static_cast<int>(EventType::PutBomb)));
				_aiBomb = 2;
			}
			else
			{
				if (_wayx == 0)
					for (size_t time = 0; time < 10; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveRight)));
				else
					for (size_t time = 0; time < 10; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveLeft)));
				if (_wayy == 0)
					for (size_t time = 0; time < 10; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveUp)));
				else 
					for (size_t time = 0; time < 10; time++)
						commands.push_back(std::to_string(static_cast<int>(EventType::MoveDown)));
				if (_aix - players.x < 100 && _aiy - players.y < 100) {
					std::this_thread::sleep_for(std::chrono::milliseconds(30));
					_aiBomb = 0;
					_aix = 10000;
					_aiy = 10000;
				}
			}
			
		}
	}
	
	return commands;
}