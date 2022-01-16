/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Lose
*/

#ifndef LOSE_HPP_
#define LOSE_HPP_

#include "Scene.hpp"

class Lose : public Scene {
	public:
		Lose(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
			std::shared_ptr<IClient> client);
		~Lose() {};

		void run();

		void activate() 
		{
			_isActivate = true;
			_sound.setBuffer(_buffer);
			_sound.play();
		};

		void activate(int win) {_isActivate = true;};
		void desactivate() 
		{
			_isActivate = false;
			_sound.stop();
		};

		void handleEventChangeScene(std::shared_ptr<Scene> toActivate);

	protected:
	private:
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
};

#endif /* !LOSE_HPP_ */