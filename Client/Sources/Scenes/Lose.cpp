/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Lose
*/

#include "SFML/Audio.hpp"
#include "Lose.hpp"

Lose::Lose(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client)
    : Scene(event, device, driver, sceneManager, client)
{
	if (!_buffer.loadFromFile("../media/Sounds/Loose.ogg")) {
		throw;
	}
}

void Lose::run()
{
	static bool initialized = false;
 	irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();
	if (!initialized) {
    		env->clear();
		env->addImage(_driver->getTexture("../media/Scene/Lose.png"), irr::core::position2d<int>(100, 150));
		initialized = true;
	}
	if (_device->isWindowActive())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 125, 125, 125));
		env->drawAll();
		_driver->endScene();
	}
}

void Lose::handleEventChangeScene(std::shared_ptr<Scene> toActivate)
{
	if (_event->IsKeyDown(irr::KEY_ACCEPT)) {
		desactivate();
		toActivate->activate();
	}
}