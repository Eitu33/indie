/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include <utility>
#include <string>

namespace game_logic
{

class Wall
{
public:
    Wall(const std::pair<float, float> &position, bool isTough);
    ~Wall() = default;

    void destroy();
    void serialize(std::string &sdata, bool fserial, bool force = false) const;
    std::pair<float, float> getPosition() const;
    bool bonusMode() const;
    bool isDestroyed() const;
    bool isTough() const;
    unsigned int getBonus() const;

private:
    std::pair<float, float> _position;
    unsigned short _bonus;
    bool _bonusMode;
    bool _isTough;
    bool _isDestroyed;
};

} // namespace game_logic

#endif /* !WALL_HPP_ */
