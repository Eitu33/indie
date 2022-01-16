/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "BombHandler.hpp"
#include <memory>

namespace game_logic
{

class Player
{
public:
    Player(unsigned int id, std::pair<float, float> position, const bool &isAlive = true);
    ~Player() = default;

    void dropBomb(std::vector<Bomb> &bombs);
    void update(std::vector<Wall> &walls, std::vector<Bomb> &bombs);
    bool isAlive();
    void setAlive(const bool &alive) {_isAlive = alive;};
    void serialize(std::string &sdata);
    void move(std::vector<Wall> &walls, Direction direction);
    unsigned int getId() const;
    void setSpeed(unsigned int speed);
    void setPosition(std::pair<float, float> position);

private:
    std::unique_ptr<BombHandler> _bombHandler;
    std::pair<float, float> _position;
    Direction _direction;
    short _noMove;
    unsigned int _id;
    unsigned int _speed;
    bool _isAlive;
};

} // namespace game_logic

#endif /* !PLAYER_HPP_ */
