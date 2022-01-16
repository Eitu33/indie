/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <vector>
#include <memory>
#include <thread>

#include "SFML/Audio.hpp"

#include "LocalPlay.hpp"
#include "WaitingScreen.hpp"
#include "InGame.hpp"
#include "Lose.hpp"
#include "Win.hpp"

class SceneManager {
	public:
		SceneManager(const bool &isLocal, const bool &isNew) : _isLocal(isLocal), _isNew(isNew) {};
		~SceneManager() {};

		void init(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
				const int &numberOfPlayers);

		void run();

	protected:
	private:
		bool _isLocal;
		bool _isNew;
		std::vector<std::shared_ptr<Scene>> _scenes;
	
		std::thread _clientThread;
		std::shared_ptr<IClient> _client;
		std::shared_ptr<Client> _clientServ;
		std::shared_ptr<LocalPlay> _clientLoc;
		bool _isConnected = false;
		Event *_event;
    		irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;

		sf::Music _music;
		sf::Sound _sound;
		sf::SoundBuffer _bufferWin;
		sf::SoundBuffer _bufferLose;
};

#endif /* !SCENEMANAGER_HPP_ */