/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** WaitingScreen
*/

#ifndef WAITINGSCREEN_HPP_
#define WAITINGSCREEN_HPP_

#include <thread>

#include "Scene.hpp"

#define TOURNAMENT 0

class WaitingScreen : public Scene {
	public:
		WaitingScreen(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
				irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client);
		~WaitingScreen() {};

		void run();
		void activate() {_isActivate = true;};
		void activate(int win) {_isActivate = true;};
		void desactivate() {_isActivate = false;};

		void handleEventChangeScene(std::shared_ptr<Scene> toActivate);

	protected:
	private:
		void handleEvent() {};
};

#endif /* !WAITINGSCREEN_HPP_ */
