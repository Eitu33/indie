/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <functional>
#include <algorithm>

#include "Ai.hpp"
#include "IClient.hpp"

#include "ClientSocket.hpp"

static const char *ipServer = "127.0.0.1";
static const unsigned int port = 4250;
static const int nbFunctions = 4;

class Client : public IClient {
	public:
		Client(ClientType type, unsigned int portServer);
		~Client();
		ClientState getState(void)
		{
			return (_state);
		}
		void setState(ClientState state)
		{
			_state = state;
		}
		void run(void);

		SceneFromClientState getSceneState() {return _sceneState;};
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
		int getWin() {};
		void sendEvent(const std::string &event) const {_toMatch.sendPacket(event);};

		void handleEvents(const Event &keyCode) {};

		bool isLocal() const {return false;};
		bool isPaused() const {return false;};
		void setPause(const bool &isPaused) {(void)isPaused;};

		void stop() {};

	protected:
	private:
		void manageReponseMainServer(std::string reponse);
		void manageReponseInTournament(std::string reponse);
		void manageReponseInGame(std::string reponse);
		
		ClientState _state = ClientState::NOT_AUTHENTIFICATED;
		ClientType _type;
		ClientSocket _toMainServer;
		ClientSocket _toTournament;
		ClientSocket _toMatch;
		std::function<void(Client*, std::string)> _manageReponseFunctions[nbFunctions];
		bool _running = true;
		bool _firstTurn = true;
		bool _firstRecup = true;
		int _id = 0;
		game_logic::GameData _infosInGame;
		game_logic::GameData _firstInfoGame;
		game_logic::Game _gameLogic;
		SceneFromClientState _sceneState = SceneFromClientState::WAITING_FOR_LAUNCH;
		
		Ai _ai;
};

#endif /* !CLIENT_HPP_ */
