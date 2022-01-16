/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** BombHandler
*/

#ifndef BOMBHANDLER_HPP_
#define BOMBHANDLER_HPP_

#include "Bomb.hpp"
#include <ctime>
#include <vector>

namespace game_logic
{

class BombHandler
{
public:
    BombHandler(unsigned int playerId);
    ~BombHandler() = default;

    void newBomb(std::vector<Bomb> &bombs, float x, float y);
    void udpate(std::vector<Wall> &walls, std::vector<Bomb> &bombs, const std::pair<float, float> position);
    bool playerHit() const;
    void increasePower(unsigned int add);
    void increaseExpSpeed(float add);
    void increaseThreshold(unsigned int add);

private:
    unsigned int _playerId;
    unsigned int _power;
    float _expSpeed;
    unsigned int _threshold;
    unsigned int _bombCount;
    bool _playerHit;
};

} // namespace game_logic

#endif /* !BOMBHANDLER_HPP_ */
