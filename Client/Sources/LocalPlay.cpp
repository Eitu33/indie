/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** LocalPlay
*/

#include <iostream>

#include <thread>

#include "MenuPause.hpp"
#include "Save.hpp"
#include "EventKeyEnum.hpp"
#include "LocalPlay.hpp"

LocalPlay::LocalPlay(const int &NumberOfPlayers, const bool &isNew)
{
	std::vector<unsigned int> v = {0, 1, 2, 3};
	Save save;

	if (!isNew) {
		std::string data = save.loadGame();
		if (data == "") {
			_game = std::shared_ptr<game_logic::Game>(new game_logic::Game(v));
		} else
			_game = std::shared_ptr<game_logic::Game>(new game_logic::Game(v, save.loadGame()));
	} else
		_game = std::shared_ptr<game_logic::Game>(new game_logic::Game(v));
	_numberOfPlayer = NumberOfPlayers;
	for (auto i = _numberOfPlayer; i < 4; i++) {
		_AIs.push_back(std::make_pair(i, Ai()));
	}
}

void LocalPlay::manageReponseInGame(std::string reponse)
{
	if (_firstRecup) {
		_firstRecup = false;
		_id = std::atoi(reponse.substr(0, reponse.find(':')).c_str());
		reponse = reponse.substr(reponse.find(":") + 1, reponse.length());
		_firstInfoGame = _gameLogic.deserialize(std::string(reponse));
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	_infosInGame = _gameLogic.deserialize(std::string(reponse));
	for (auto &ai : _AIs) {
		std::vector<std::string> commands = ai.second.autoPlay(_infosInGame, ai.first);
		for (auto &command : commands) {
			EventType event = static_cast<EventType>(std::atoi(command.c_str()));
			if (event == EventType::PutBomb)
				_game->dropBomb(ai.first);
			else
				_game->move(ai.first, static_cast<game_logic::Direction>(event));
		}
	}
}

void LocalPlay::manageGameEvents()
{
	static bool firstTurn = true;

	if (_isPaused) {
		return;
	}

	if (!_game->update()) {
		_winner = _game->getWinnersId()[0];
		_state = SceneFromClientState::WIN;
		_run = false;
	}

	std::string serializedString = _game->serialize();
	if (firstTurn)
		serializedString = "0:" + serializedString;
	manageReponseInGame(serializedString);
	firstTurn = false;
}

void LocalPlay::handleEvents(const Event &keyCode)
{
	if (keyCode.IsKeyDown(irr::KEY_ESCAPE)) {
		_isPaused = true;
	}
	//player one
	if (keyCode.IsKeyDown(irr::KEY_RIGHT)) {
		_game->move(0, static_cast<game_logic::Direction>(EventType::MoveRight));
	}
	if (keyCode.IsKeyDown(irr::KEY_LEFT)) {
		_game->move(0, static_cast<game_logic::Direction>(EventType::MoveLeft));
	}
	if (keyCode.IsKeyDown(irr::KEY_UP)) {
		_game->move(0, static_cast<game_logic::Direction>(EventType::MoveUp));
	}
	if (keyCode.IsKeyDown(irr::KEY_DOWN)) {
		_game->move(0, static_cast<game_logic::Direction>(EventType::MoveDown));
	}
	if (keyCode.IsKeyDown(irr::KEY_RSHIFT)) {
		_game->dropBomb(0);
	}

	if (_numberOfPlayer == 1)
		return; 
	//player two
	if (keyCode.IsKeyDown(irr::KEY_KEY_D)) {
		_game->move(1, static_cast<game_logic::Direction>(EventType::MoveRight));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_Q)) {
		_game->move(1, static_cast<game_logic::Direction>(EventType::MoveLeft));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_Z)) {
		_game->move(1, static_cast<game_logic::Direction>(EventType::MoveUp));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_S)) {
		_game->move(1, static_cast<game_logic::Direction>(EventType::MoveDown));
	}
	if (keyCode.IsKeyDown(irr::KEY_LSHIFT)) {
		_game->dropBomb(1);
	}

	if (_numberOfPlayer == 2)
		return;
	//player three
	if (keyCode.IsKeyDown(irr::KEY_KEY_B)) {
		_game->move(2, static_cast<game_logic::Direction>(EventType::MoveRight));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_C)) {
		_game->move(2, static_cast<game_logic::Direction>(EventType::MoveLeft));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_F)) {
		_game->move(2, static_cast<game_logic::Direction>(EventType::MoveUp));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_V)) {
		_game->move(2, static_cast<game_logic::Direction>(EventType::MoveDown));
	}
	if (keyCode.IsKeyDown(irr::KEY_SPACE)) {
		_game->dropBomb(2);
	}

	if (_numberOfPlayer == 3)
		return;
	//player four
	if (keyCode.IsKeyDown(irr::KEY_KEY_L)) {
		_game->move(3, static_cast<game_logic::Direction>(EventType::MoveRight));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_J)) {
		_game->move(3, static_cast<game_logic::Direction>(EventType::MoveLeft));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_I)) {
		_game->move(3, static_cast<game_logic::Direction>(EventType::MoveUp));
	}
	if (keyCode.IsKeyDown(irr::KEY_KEY_K)) {
		_game->move(3, static_cast<game_logic::Direction>(EventType::MoveDown));
	}
	if (keyCode.IsKeyDown(irr::KEY_RETURN)) {
		_game->dropBomb(3);
	}
}

void LocalPlay::run(void)
{
	while (_run) {
		manageGameEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}