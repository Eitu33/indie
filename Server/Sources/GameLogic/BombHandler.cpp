/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** BombHandler
*/

#include "BombHandler.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

static const int TILESIZE = 50;
static const int TRESHOLD_UPVALUE = 1;
static const float MEXP_SPEED = 2.5f;

game_logic::BombHandler::BombHandler(unsigned int playerId)
    : _playerId(playerId),
      _power(1),
      _expSpeed(0.f),
      _threshold(1),
      _bombCount(0),
      _playerHit(false)
{
}

void game_logic::BombHandler::newBomb(std::vector<Bomb> &bombs, float x, float y)
{
    int q = (int)x % TILESIZE;
    x = (q > TILESIZE / 2) ? std::trunc(x - q) + TILESIZE : std::trunc(x - q);
    q = (int)y % TILESIZE;
    y = (q > TILESIZE / 2) ? std::trunc(y - q) + TILESIZE : std::trunc(y - q);
    int counter = std::count_if(bombs.begin(), bombs.end(), [&](Bomb const &bomb) {
        return bomb.isOwner(_playerId);
    });
    if (counter - _bombCount < _threshold)
    {
        bombs.push_back(Bomb(_playerId, x, y, _power, _expSpeed));
    }
}

void game_logic::BombHandler::udpate(
    std::vector<Wall> &walls,
    std::vector<Bomb> &bombs,
    const std::pair<float, float> position)
{
    _bombCount = 0;
    for (auto it = bombs.begin(); it != bombs.end(); it++)
    {
        it->update();
        it->wallsCollider(walls);
        it->bombsCollider(bombs);
        _playerHit = it->playerHit(position);
        if (_playerHit)
            return;
        if (it->isOwner(_playerId) && it->getState() == Bomb::BombState::OVER)
            _bombCount += 1;
    }
}

bool game_logic::BombHandler::playerHit() const
{
    return _playerHit;
}

void game_logic::BombHandler::increasePower(unsigned int add)
{
    _power += add;
}

void game_logic::BombHandler::increaseExpSpeed(float add)
{
    _expSpeed += add;
    if (_expSpeed > MEXP_SPEED)
        _expSpeed = MEXP_SPEED;
}

void game_logic::BombHandler::increaseThreshold(unsigned int add)
{
    _threshold += add;
}
