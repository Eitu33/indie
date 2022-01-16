/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <memory>
#include <iostream>

#include "Client.hpp"
#include "Event.hpp"

class Scene {
	public:
		Scene(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, 
			irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client)
		: _event(event), _device(device), _driver(driver), _sceneManager(sceneManager), _client(client) {};
		Scene () {};
		~Scene() {};

		virtual void run() = 0;

		virtual void activate() = 0;
		virtual void activate(int win) = 0;
		virtual void desactivate() = 0;
		bool isActivate() {return _isActivate;};

		virtual void handleEventChangeScene(std::shared_ptr<Scene> toActivate) = 0;

	protected:
		bool _isActivate = false;
		std::shared_ptr<IClient> _client;
		bool _run = true;
		Event *_event;
    		irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;
		irr::video::ITexture *_title;
	private:
};
#endif /* !SCENE_HPP_ */