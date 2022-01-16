/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Game
*/

#include <iostream>

#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

const int PLAYERS_NUMBER = 4;

game_logic::Game::Game(std::vector<unsigned int> idv)
{
    MapGeneration mapGen(15, 10);
    mapGen.generateMap();
    auto twalls = mapGen.getPosByChar('X', 50);
    auto dwalls = mapGen.getPosByChar('D', 50);
    auto ppos = mapGen.getPosByChar('P', 50);
    srand((unsigned)time(0));

    for (auto it = twalls.begin(); it != twalls.end(); it++)
        _walls.push_back(Wall(std::pair<float, float>(it->first, it->second), true));
    for (auto it = dwalls.begin(); it != dwalls.end(); it++)
        _walls.push_back(Wall(std::pair<float, float>(it->first, it->second), false));
    for (std::size_t i = 0; i < PLAYERS_NUMBER; i++)
        _players.push_back(std::unique_ptr<Player>(new Player(idv[i], std::pair<float, float>(ppos[i].first, ppos[i].second))));
}

game_logic::Game::Game(std::vector<unsigned int> idv, const std::string &loadGame)
{
    initFromGameData(loadGame);
}

void game_logic::Game::move(short player, Direction direction)
{
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if ((*it)->getId() == player && (*it)->isAlive())
            (*it)->move(_walls, direction);
    }
}

void game_logic::Game::dropBomb(short player)
{
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if ((*it)->getId() == player && (*it)->isAlive())
            (*it)->dropBomb(_bombs);
    }
}

/*
/ also used to check if the game is still going
*/
bool game_logic::Game::update()
{
    if (_winnersId.size() == PLAYERS_NUMBER - 1 || _winnersId.size() == PLAYERS_NUMBER)
    {
        auto winner = std::find_if(_players.begin(), _players.end(), [&](std::unique_ptr<Player> &player) {
        return player->isAlive() == true;});
        if (winner != _players.end())
            _winnersId.push_back((*winner)->getId());
        return false;
    }
    for (auto it = _walls.begin(); it != _walls.end();)
    {
        if (it->isDestroyed())
            it = _walls.erase(it);
        else
            it++;
    }
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        (*it)->update(_walls, _bombs);
        if ((*it)->isAlive() == false)
        {
            auto checkId = find_if(_winnersId.begin(), _winnersId.end(), [&](unsigned int const &id) {
                return id == (*it)->getId();
            });
            if (checkId == _winnersId.end())
            {
                _winnersId.push_back((*it)->getId());
            }
        }
    }
    return true;
}

std::string game_logic::Game::serialize(const bool &force)
{
    std::string sdata("<players>");
    for (auto it = _players.begin(); it != _players.end(); it++)
        (*it)->serialize(sdata);
    sdata += "<bombs>";
    for (auto it = _bombs.begin(); it != _bombs.end(); it++)
        it->serialize(sdata);
    sdata += "<walls>";
    for (auto it = _walls.begin(); it != _walls.end(); it++) {
        if (fserial || force) {
            it->serialize(sdata, true, true);
        }
        else
            it->serialize(sdata, false);
    }
    if (!force) {
        fserial = false;
    }
    return sdata;
}

std::vector<unsigned int> game_logic::Game::getWinnersId() const
{
    return _winnersId;
}

game_logic::GameData game_logic::Game::deserialize(const std::string sdata, const bool &force)
{
    GameData gm;
    std::vector<std::string> strs;
    boost::split(strs, sdata, boost::is_any_of("<>"));
    std::vector<std::string> players;
    boost::split(players, strs[2], boost::is_any_of(";"));
    std::vector<std::string> bombs;
    boost::split(bombs, strs[4], boost::is_any_of(";"));
    std::vector<std::string> walls;
    boost::split(walls, strs[6], boost::is_any_of(";"));

    for (std::size_t i = 0; i < players.size() - 1; i++)
    {
        std::vector<std::string> sp;
        PlayerData pm;
        boost::split(sp, players[i], boost::is_any_of(","));
        pm.id = boost::lexical_cast<unsigned int>(sp[0]);
        pm.x = boost::lexical_cast<float>(sp[1]);
        pm.y = boost::lexical_cast<float>(sp[2]);
        pm.direction = (Direction)boost::lexical_cast<int>(sp[3]);
        pm.isAlive = (sp[4] == "1") ? 1 : 0;
        gm.players.push_back(pm);
    }
    for (std::size_t i = 0; i < bombs.size() - 1; i++)
    {
        std::vector<std::string> sp;
        BombData bm;
        boost::split(sp, bombs[i], boost::is_any_of(","));
        bm.x = boost::lexical_cast<float>(sp[0]);
        bm.y = boost::lexical_cast<float>(sp[1]);
        /* UP DOWN LEFT RIGHT */
        for (std::size_t j = 0; j < 4; j++)
            bm.explosionSize[j] = boost::lexical_cast<int>(sp[j + 2]);
        gm.bombs.push_back(bm);
    }
    for (std::size_t i = 0; i < walls.size() - 1; i++)
    {
        std::vector<std::string> sp;
        WallData wm;
        boost::split(sp, walls[i], boost::is_any_of(","));
        wm.x = boost::lexical_cast<float>(sp[0]);
        wm.y = boost::lexical_cast<float>(sp[1]);
        wm.isBonus = (sp[2] == "1") ? true : false;
        wm.bonus = (Bonus)boost::lexical_cast<int>(sp[3]);
        wm.isTough = false;
        if (fdserial)
        {
            wm.isTough = (sp[4] == "1") ? true : false;
        }
        gm.walls.push_back(wm);
    }
    if (!force)
        fdserial = false;
    return gm;
}

void game_logic::Game::initFromGameData(const std::string &stringData)
{
    game_logic::GameData loadData = deserialize(stringData, true);
    for (auto &elem : loadData.players)
    {
        _players.push_back(std::unique_ptr<Player>(new Player(elem.id, std::pair<float, float>(elem.x, elem.y), elem.isAlive)));
    }

    for (auto &elem : loadData.walls) {
        _walls.push_back(Wall(std::pair<float, float>(elem.x, elem.y), elem.isTough));
    }

    for (auto &elem : loadData.bombs)
        _bombs.push_back(Bomb(elem.x, elem.y, 2, Bomb::BombState::DROPPED));
}