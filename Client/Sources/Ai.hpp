/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Ai
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <functional>
#include "Game.hpp"
#include <algorithm>

class Ai {
    public:
        Ai() = default;
        ~Ai() = default;

        std::vector<std::string> autoPlay(const game_logic::GameData &infos, const int &id);
    
    private:
        int _aiBomb = 0;
		int _aix = 100000;
		int _aiy = 100000;
		int _wayx;
		int _wayy;
};

#endif /* !AI_HPP_ */