/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** LocalPlay
*/

#ifndef LOCALPLAY_HPP_
#define LOCALPLAY_HPP_

#include "Ai.hpp"
#include "Save.hpp"

#include "IClient.hpp"

class LocalPlay : public IClient {
	public:
		LocalPlay(const int &NumberOfPlayers, const bool &isNew);
		~LocalPlay() = default;

		ClientState getState(void) {return ClientState::IN_GAME;};
		void setState(ClientState state) {(void)state;};
		void run(void);

		SceneFromClientState getSceneState() {return _state;};

		game_logic::GameData getInfosInGame() {
			if (_firstTurn) {
				_firstTurn = false;
				return _firstInfoGame;
			} else {
				return _infosInGame;
			}
		};
		
		bool infosSet() {return _firstTurn;};
		int getID() {return _id;};
		int getWin() {return _winner;};
		void sendEvent(const std::string &event) const {};
		void handleEvents(const Event &keyCode);

		bool isLocal() const {return true;};
		bool isPaused() const {return _isPaused;};
		void setPause(const bool &isPaused) {_isPaused = isPaused;};

		void stop() 
		{
			Save save;
			save.saveGame(_game->serialize(true));

			_run = false;
		};

	protected:
	private:
		void manageReponseInGame(std::string reponse);
		void manageGameEvents();

		int _numberOfPlayer;
		std::shared_ptr<game_logic::Game> _game;
		std::vector<std::pair<unsigned short, Ai>> _AIs;
		
		bool _firstRecup = true;
		bool _firstTurn = true;
		bool _isPaused = false;

		int _id = 0;
		game_logic::GameData _infosInGame;
		game_logic::GameData _firstInfoGame;
		game_logic::Game _gameLogic;

		int _winner = -1;
		SceneFromClientState _state = SceneFromClientState::IN_GAME;
		bool _run = true;
};

#endif /* !LOCALPLAY_HPP_ */