/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** WaitingScreen
*/

#include <irrlicht.h>

#include "Event.hpp"
#include "WaitingScreen.hpp"

WaitingScreen::WaitingScreen(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
				irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client)
    : Scene(event, device, driver, sceneManager, client)
{
}

void WaitingScreen::run()
{
	static bool initialized = false;
 	irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();
	if (!initialized) {
    		env->clear();
		env->addImage(_driver->getTexture("waiting.png"), irr::core::position2d<int>(100, 150));
		initialized = true;
	}
	handleEvent();
	if (_device->isWindowActive())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
		env->drawAll();
		_driver->endScene();
	}
}
;
void WaitingScreen::handleEventChangeScene(std::shared_ptr<Scene> toActivate)
{
	if (_event->IsKeyDown(irr::KEY_ACCEPT)) {
		desactivate();
		toActivate->activate();
	}
}