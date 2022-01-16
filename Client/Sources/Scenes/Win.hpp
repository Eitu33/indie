/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Win
*/

#ifndef WIN_HPP_
#define WIN_HPP_

#include "SFML/Audio.hpp"
#include "Scene.hpp"

class Win : public Scene {
	public:
		Win(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
			irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client, const bool &isLocal);
		~Win() {};

		void run();

		void activate() {_isActivate = true;};
		void activate(int win) 
		{
			_isActivate = true;
			_sound.setBuffer(_buffer);
			_sound.play();
			_win = win;
		};
		
		void desactivate() 
		{
			_isActivate = false;
			_sound.stop();
		};

		void handleEventChangeScene(std::shared_ptr<Scene> toActivate);
		void setWin(const int &win) {_win = win;};

	protected:
	private:
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
		bool _local;
		int _win;
};

#endif /* !WIN_HPP_ */
