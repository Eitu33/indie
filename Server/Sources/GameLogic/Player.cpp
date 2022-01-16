/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"
#include "Bonus.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

static const int HITBOX = 50;
static const int PHIT = 30;
static const int NOMOVE_TRESHOLD = 10;
static const int TILESIZE = 50;

game_logic::Player::Player(unsigned int id, std::pair<float, float> position, const bool &isAlive)
    : _bombHandler(new BombHandler(id)),
      _position(position),
      _direction(Direction::NONE),
      _noMove(0),
      _id(id),
      _speed(5),
      _isAlive(isAlive)
{
}

void game_logic::Player::dropBomb(std::vector<Bomb> &bombs)
{
    if (_isAlive == false)
        return;
    std::pair<float, float> roundedPos;
    int q = (int) _position.first % TILESIZE;
    roundedPos.first = (q > TILESIZE / 2) ? std::trunc(_position.first - q) + TILESIZE : std::trunc(_position.first - q);
    q = (int)_position.second % TILESIZE;
    roundedPos.second = (q > TILESIZE / 2) ? std::trunc(_position.second - q) + TILESIZE : std::trunc(_position.second - q);
    auto it = find_if(bombs.begin(), bombs.end(), [&](Bomb const &bomb) {
        return roundedPos == bomb.getPosition();
    });
    if (it == bombs.end())
    {
        _bombHandler->newBomb(bombs, _position.first, _position.second);
    }
}

void game_logic::Player::update(std::vector<Wall> &walls, std::vector<Bomb> &bombs)
{
    if (!_isAlive)
        return;
    _noMove += 1;
    if (_noMove >= NOMOVE_TRESHOLD)
        _direction = NONE;
    _bombHandler->udpate(walls, bombs, _position);
    _isAlive = !_bombHandler->playerHit();
}

bool game_logic::Player::isAlive()
{
    return _isAlive;
}

void game_logic::Player::serialize(std::string &sdata)
{
    sdata += boost::lexical_cast<std::string>(_id) + ",";
    sdata += boost::lexical_cast<std::string>(_position.first) + ",";
    sdata += boost::lexical_cast<std::string>(_position.second) + ",";
    sdata += boost::lexical_cast<std::string>(_direction) + ",";
    sdata += (_isAlive) ? "1;" : "0;";
}

void game_logic::Player::move(std::vector<Wall> &walls, Direction direction)
{
    if (_isAlive == false)
        return;
    _direction = direction;
    _noMove = 0;
    switch (direction)
    {
    case Direction::UP:
        _position.second -= _speed;
        break;
    case Direction::DOWN:
        _position.second += _speed;
        break;
    case Direction::LEFT:
        _position.first -= _speed;
        break;
    case Direction::RIGHT:
        _position.first += _speed;
        break;
    default:
        break;
    }
    auto it = find_if(walls.begin(), walls.end(), [&](Wall const &wall) {
        return _position.first > wall.getPosition().first - PHIT && _position.first < wall.getPosition().first + HITBOX &&
        _position.second > wall.getPosition().second - PHIT && _position.second < wall.getPosition().second + HITBOX && !wall.bonusMode();
    });
    if (it != walls.end()) {
        switch (direction)
        {
        case Direction::UP:
            _position.second = it->getPosition().second + HITBOX;
            break;
        case Direction::DOWN:
            _position.second = it->getPosition().second - PHIT;
            break;
        case Direction::LEFT:
            _position.first = it->getPosition().first + HITBOX;
            break;
        case Direction::RIGHT:
            _position.first = it->getPosition().first - PHIT;
            break;
        default:
            break;
        }
    }
    it = find_if(walls.begin(), walls.end(), [&](Wall const &wall) {
        return _position.first > wall.getPosition().first - PHIT && _position.first < wall.getPosition().first + HITBOX &&
        _position.second > wall.getPosition().second - PHIT && _position.second < wall.getPosition().second + HITBOX && wall.bonusMode();
    });
    if (it == walls.end())
        return;
    switch (it->getBonus())
    {
    case Bonus::POWER:
        _bombHandler->increasePower(1);
        break;
    case Bonus::SPEED:
        _bombHandler->increaseExpSpeed(0.25f);
        break;
    case Bonus::STACK:
        _bombHandler->increaseThreshold(1);
        break;
    case Bonus::PASST:
        // Work in progress
        break;
    default:
        break;
    }
    it->destroy();
}

unsigned int game_logic::Player::getId() const
{
    return _id;
}

void game_logic::Player::setSpeed(unsigned int speed)
{
    _speed = speed;
}

void game_logic::Player::setPosition(std::pair<float, float> position)
{
    _position = position;
}
