/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** GameData
*/

#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include "Direction.hpp"
#include "Bonus.hpp"
#include <vector>

namespace game_logic
{

struct PlayerData
{
    unsigned int id;
    float x;
    float y;
    Direction direction;
    bool isAlive;
};

struct BombData
{
    float x;
    float y;
    int explosionSize[4];
};

struct WallData
{
    float x;
    float y;
    bool isBonus;
    Bonus bonus;
    bool isTough;
};

struct GameData
{
    std::vector<struct PlayerData> players;
    std::vector<struct BombData> bombs;
    std::vector<struct WallData> walls;
};

} // namespace game_logic

#endif /* !GAMEDATA_HPP_ */
