/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuNbPlayer
*/

#ifndef MENUNBPLAYER_HPP_
#define MENUNBPLAYER_HPP_

#define ONE 0
#define TWO 1
#define THREE 2
#define FOUR 3
#define ESC 1
#define ENTER 2
#define SPACE 3
#define CLEAR 4

#include "Menu.hpp"
#include "Event.hpp"
#include "Button.hpp"
#include "SFML/Audio.hpp"

#include "irrlicht.h"
#include "driverChoice.h"

#include <stdbool.h>
#include <thread>
#include <chrono>
#include <iostream>

class MenuNbPlayer {
	public:
		MenuNbPlayer(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager, int32_t sound);
		~MenuNbPlayer() = default;
		void addIndex();
		void changeIndex();
		void checkChoice(irr::gui::IGUIEnvironment *env, Button *one, Button *two, Button *three, Button *four);
		void checkInput(irr::gui::IGUIEnvironment *env, Button *one, Button *two, Button *three, Button *four);
        void initButton(Button *one, Button *two, Button *three, Button *four);
		void initCam();
		void initParticle();
		void initSprite(irr::gui::IGUIEnvironment *env);
        void printButton(irr::gui::IGUIEnvironment *env, Button *one, Button *two, Button *three, Button *four);
		void menuLoop();
		void subIndex();
		int32_t getNbPlayer();
		void pressManager(int key);
		void updateNbPlayer(Button *button, int nb);
		bool _goGame = false;
		void loadSound();

	protected:
	private:
		Event *_event;
		bool _isPressed = false;
		int32_t _index = 1;
		int32_t _gameMode = -1;
		int32_t _keyIsPressed = 0;
		int32_t _nbPlayer = 1;
		bool _changeIndex = false;
		bool _isChoose = false;
		bool _isReleased = false;
		bool _run = true;
    	irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;
	    irr::video::ITexture *_title;
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
		sf::Sound _select;
		sf::SoundBuffer _buffer2;
		int32_t _nbSound;
};

#endif /* !MENUNBPLAYER_HPP_ */
