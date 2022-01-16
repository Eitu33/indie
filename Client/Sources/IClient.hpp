/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include "Event.hpp"
#include "Game.hpp"

enum class SceneFromClientState {
	WAITING_FOR_LAUNCH,
	IN_GAME,
	WIN,
	LOSE
};

enum ClientType {
	IA,
	PERSON
};

enum class ClientState {
	NOT_AUTHENTIFICATED,
	WAITING_FOR_LAUNCH,
	CONNECTED_TO_TOURNAMENT,
	IN_GAME
};

class IClient {
	public:
		~IClient() {};

		virtual ClientState getState(void) = 0;
		virtual void setState(ClientState state) = 0;
		virtual void run(void) = 0;

		virtual SceneFromClientState getSceneState() = 0;
		virtual game_logic::GameData getInfosInGame() = 0;
		virtual bool infosSet() = 0;
		virtual int getID() = 0;
		virtual int getWin() = 0;
		virtual void sendEvent(const std::string &event) const = 0;
		virtual void handleEvents(const Event &keyCode) = 0;
		virtual bool isLocal() const = 0;
		virtual bool isPaused() const = 0;
		virtual void setPause(const bool &isPaused) = 0;
		virtual void stop() = 0;

	protected:
	private:
};

#endif /* !ICLIENT_HPP_ */