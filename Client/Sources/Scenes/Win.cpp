/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Win
*/

#include "Win.hpp"

Win::Win(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client, const bool &isLocal)
    : Scene(event, device, driver, sceneManager, client), _local(isLocal)
{
	if (!_buffer.loadFromFile("../media/Sounds/Win.ogg")) {
		throw;
	}
}

void Win::run()
{
	static bool initialized = false;
	char *textures[4] = {(char *)"../media/Scene/Player4.png", (char *)"../media/Scene/Player1.png",
	(char *)"../media/Scene/Player2.png", (char *)"../media/Scene/Player3.png"};

 	irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();
	if (!initialized) {
    		env->clear();
		if (!_local) {
			env->addImage(_driver->getTexture("../media/Scene/Win.png"), irr::core::position2d<int>(100, 150));
		} else {
			env->addImage(_driver->getTexture(textures[_win]), irr::core::position2d<int>(300, 150));
		}
		initialized = true;
	}

	if (_device->isWindowActive())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
		env->drawAll();
		_driver->endScene();
	}
}

void Win::handleEventChangeScene(std::shared_ptr<Scene> toActivate)
{
	if (_event->IsKeyDown(irr::KEY_ACCEPT)) {
		desactivate();
		toActivate->activate();
	}
}