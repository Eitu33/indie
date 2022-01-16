/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** SceneManager
*/

#include <iostream>
#include <thread>
#include <chrono>
#include "MenuPause.hpp"
#include "SceneManager.hpp"

void SceneManager::init(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
				const int &numberOfPlayers) 
{
	//Client Creation
	if (_isLocal) {
		_clientLoc = std::shared_ptr<LocalPlay>(new LocalPlay(numberOfPlayers, _isNew));
		_client = std::shared_ptr<IClient>(_clientLoc);
	}
	else {
		_clientServ = std::make_shared<Client>(ClientType::PERSON, port);
		_client = std::shared_ptr<IClient>(_clientServ);
	}

	//Scenes Creation
	WaitingScreen *waitScreen = new WaitingScreen(event, device, driver, sceneManager, _client);
	waitScreen->activate();
	_scenes.push_back(std::shared_ptr<Scene>(waitScreen));

	InGame *inGame = new InGame(event, device, driver, sceneManager, _client);
	inGame->desactivate();
	_scenes.push_back(std::shared_ptr<Scene>(inGame));

	Lose *lose = new Lose(event, device, driver, sceneManager, _client);
	lose->desactivate();
	_scenes.push_back(std::shared_ptr<Scene>(lose));

	Win *win = new Win(event, device, driver, sceneManager, _client, _isLocal);
	win->desactivate();
	_scenes.push_back(std::shared_ptr<Scene>(win));

	_event = event;
	_device = device;
	_driver = driver;
	_sceneManager = sceneManager;

	if (!_music.openFromFile("music.ogg")) {
		throw;
	}
};

void SceneManager::run()
{
	_music.play();
	if (_isLocal)
		_clientThread = std::thread(&LocalPlay::run, _clientLoc);
	else
		_clientThread = std::thread(&Client::run, _clientServ);
	_isConnected = true;

	while (_device->run()) {
		for (auto &elem : _scenes) {
			if (elem->isActivate()) {
				elem->run();
			}

			if ((_event->IsKeyDown(irr::KEY_ESCAPE))) {
				if (_scenes[2]->isActivate() || _scenes[3]->isActivate()) {
					_client->stop();
					_clientThread.join();
					_sceneManager->clear();
					return;
				}
			}

			if (_scenes[0]->isActivate() == false && _client->getSceneState() == SceneFromClientState::WAITING_FOR_LAUNCH) {
				for (auto &elems : _scenes)
					elems->desactivate();
				_scenes[0]->activate();
			}

			if (_scenes[1]->isActivate() == false && _client->getSceneState() == SceneFromClientState::IN_GAME) {
				for (auto &elems : _scenes)
					elems->desactivate();
				_sceneManager->clear();
				irr::scene::ICameraSceneNode* camera = _sceneManager->addCameraSceneNodeFPS(0, 0, 0, -1, NULL, 5);
				camera->setTarget(irr::core::vector3df(300.0f, 0.0f, 425.0f));
				camera->setPosition(irr::core::vector3df(320.0f, 500.0f, 425.0f));
				_scenes[1] = std::shared_ptr<Scene>(new InGame(_event, _device, _driver, _sceneManager, _client));
				_scenes[1]->activate();
			}

			if (_scenes[2]->isActivate() == false && _client->getSceneState() == SceneFromClientState::LOSE) {
				_sound.stop();
				_sound.setBuffer(_bufferLose);
				_sound.play();
				for (auto &elems : _scenes)
					elems->desactivate();
				_scenes[2]->activate();
			}

			if (_scenes[3]->isActivate() == false && _client->getSceneState() == SceneFromClientState::WIN) {
				_music.stop();
				for (auto &elems : _scenes)
					elems->desactivate();
				_scenes[3]->activate(_client->getWin());
			}

			if (_client->isPaused()) {
				MenuPause menuPause(_event, _device, _driver, _sceneManager);
				menuPause.menuLoop();
				irr::scene::ICameraSceneNode* camera = _sceneManager->addCameraSceneNodeFPS(0, 0, 0, -1, NULL, 5);
				camera->setTarget(irr::core::vector3df(300.0f, 0.0f, 425.0f));
				camera->setPosition(irr::core::vector3df(320.0f, 500.0f, 425.0f));
				_client->setPause(false);
				if (menuPause.getChoice() == MenuPause::PauseKey::mainMenu) {
					_client->stop();
					_clientThread.join();
					_sceneManager->clear();
					return;
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	_client->stop();
};