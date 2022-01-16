/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../MapGenerator/MapGeneration.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include "Wall.hpp"

namespace game_logic
{

class Game
{
public:
    Game(std::vector<unsigned int> idv);
    Game(std::vector<unsigned int> idv, const std::string &stringData);
    Game() = default;
    ~Game() = default;

    void move(short player, Direction direction);
    void dropBomb(short player);
    bool update();
    std::string serialize(const bool &forceSerialize = false);
    GameData deserialize(const std::string sdata, const bool &force = false);
    void initFromGameData(const std::string &loadData);
    std::vector<unsigned int> getWinnersId() const;

private:
    std::vector<std::unique_ptr<Player>> _players;
    std::vector<Wall> _walls;
    std::vector<Bomb> _bombs;
    std::vector<unsigned int> _winnersId;
    bool fserial = true;
    bool fdserial = true;
};

} // namespace game_logic

#endif /* !GAME_HPP_ */
