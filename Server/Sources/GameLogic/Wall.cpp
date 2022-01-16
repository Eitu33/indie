/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Wall
*/

#include "Wall.hpp"
#include "Bonus.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/lexical_cast.hpp>

const int BONUS_RAND = 5;

game_logic::Wall::Wall(const std::pair<float, float> &position, bool isTough)
    : _position(position),
      _bonus(isTough ? 0 : std::rand() % BONUS_RAND + 1),
      _bonusMode(false),
      _isTough(isTough),
      _isDestroyed(false)
{
}

void game_logic::Wall::destroy()
{
    if ((_bonus >= Bonus::POWER && _bonus <= Bonus::STACK) && _bonusMode == false)
        _bonusMode = true;
    else
        _isDestroyed = true;
}

void game_logic::Wall::serialize(std::string &sdata, bool fserial, bool force) const
{
    if (!fserial && (!_isDestroyed && !_bonusMode)) {
        if (!force)
            return;
        else if (_isDestroyed)
            return;
    }
    sdata += boost::lexical_cast<std::string>(_position.first) + ",";
    sdata += boost::lexical_cast<std::string>(_position.second) + ",";
    sdata += _bonusMode ? "1," : "0,";
    sdata += boost::lexical_cast<std::string>(_bonus);
    if (fserial)
        sdata += _isTough ? ",1" : ",0";
    sdata += ";";
}

std::pair<float, float> game_logic::Wall::getPosition() const
{
    return _position;
}

bool game_logic::Wall::bonusMode() const
{
    return _bonusMode;
}

bool game_logic::Wall::isDestroyed() const
{
    return _isDestroyed;
}

bool game_logic::Wall::isTough() const
{
    return _isTough;
}

unsigned int game_logic::Wall::getBonus() const
{
    return _bonus;
}
