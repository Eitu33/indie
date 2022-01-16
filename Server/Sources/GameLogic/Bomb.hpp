/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Wall.hpp"
#include "Direction.hpp"
#include <ctime>
#include <vector>
#include <memory>
#include <time.h>

#if _WIN64
typedef struct timestruct {
	long tv_sec;
	long tv_nsec;
} timestruct;    //header part
#endif
#if __linux__
typedef struct timespec timestruct;
#endif

namespace game_logic
{

class Bomb
{
public:
    enum class BombState
    {
        DROPPED,
        DETONATED,
        OVER
    };

    Bomb(unsigned int playerId, float x, float y, unsigned int power, float expSpeed);
    Bomb(float x, float y, unsigned int power);
    Bomb(float x, float y, unsigned int power, const BombState &state);
    Bomb(float x, float y, unsigned int power, float expSpeed);
    ~Bomb() = default;

    void update();
    void detonate();
    bool playerHit(std::pair<float, float> ppos);
    void wallsCollider(std::vector<Wall> &walls);
    void bombsCollider(std::vector<Bomb> &bombs);
    void serialize(std::string &sdata) const;
    BombState getState() const;
    std::pair<float, float> getPosition() const;
    bool isOwner(unsigned int id) const;

private:
    bool _playerCollider(std::pair<float, float> ppos, float x, float y);
    void _wallCollider(std::vector<Wall> &walls, Direction direction, float x, float y);
    void _bombCollider(std::vector<Bomb> &bombs, float x, float y);

    unsigned int _playerId;
    std::pair<float, float> _position;
    unsigned int _power;
    float _expSpeed;
    BombState _state;
    timestruct _startTimer;
    timestruct _expTimer;
    std::vector<int> _expSize;
};

} // namespace game_logic

#endif /* !BOMB_HPP_ */
