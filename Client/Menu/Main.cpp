/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Main
*/

#include <vector>
#include <iostream>
#include <memory>
#include <vector>

#include "Event.hpp"

#include "Menu.hpp"
#include "SceneManager.hpp"
#include "MenuPause.hpp"

#define TOURNAMENT 0

void start()
{

}

int main(int ac, char **av)
{
	Event event;
	std::vector<std::shared_ptr<Scene>> _scenes;

	auto device = irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1500, 900),
	32, false, false, false, &event);

	auto driver = device->getVideoDriver();
	auto sceneManager = device->getSceneManager();
//	MenuPause menuPause(&event, device, driver, sceneManager);
//	menuPause.menuLoop();

	try {
		while (1) {
			Menu menu(&event, device, driver, sceneManager);
			menu.menuLoop();

			if (menu.getGameMode() == -1)
				return 0;
			
			SceneManager manager(menu.getGameMode(), menu.getGameIsNew());
			irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNodeFPS(0, 0, 0, -1, NULL, 5);
			camera->setTarget(irr::core::vector3df(300.0f, 0.0f, 425.0f));
			camera->setPosition(irr::core::vector3df(320.0f, 500.0f, 425.0f));
			manager.init(&event, device, driver, sceneManager, menu.getNbPlayer());
			manager.run();
		}
	}
	catch (std::exception except) {
		std::cout <<"Errror" <<std::endl;
	}
}