/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <stdbool.h>
#include <thread>
#include <chrono>
#include <iostream>

#include "irrlicht.h"
#include "driverChoice.h"
#include "SFML/Audio.hpp"

#include "Event.hpp"
#include "Button.hpp"
#include "MenuOption.hpp"
#include "MenuMode.hpp"
#include "Client.hpp"

#define PLAY 2
#define OPTION 1
#define EXIT 0
#define CLASSIC 1
#define TOURNAMENT 0
#define NOMODE -1

class Menu {
	public:
		Menu(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, 
		irr::scene::ISceneManager *sceneManager);
		~Menu() = default;
		void addIndex();
		void changeIndex();
		void checkChoice(irr::gui::IGUIEnvironment *env);
		void checkInput(irr::gui::IGUIEnvironment *env);
		void initButton();
		void initCam();
		void initParticle();
		void initSprite(irr::gui::IGUIEnvironment *env);
		void goModeMenu(irr::gui::IGUIEnvironment *env);
		void menuLoop();
		void printButton(irr::gui::IGUIEnvironment *env);
		void goMenuOption(irr::gui::IGUIEnvironment *env);
		void subIndex();
		void drawLoop(irr::gui::IGUIEnvironment *env);
		void loadSound();
		void loadMusic();
		void initLoop(irr::gui::IGUIEnvironment *env);
		int32_t getGameMode();
		int32_t getNbPlayer();
		bool getGameIsNew();
		int32_t getNbSound();

	protected:
	private:
		Event *_event;
		bool _isPressed = false;
		int32_t _index = 2;
		int32_t _gameMode = -1;
		int32_t _nbPlayer = 0;
		bool _gameIsNew = false;
		bool _isReleased = false;
		bool _isChoose = false;
		bool _run = true;
		sf::Music _music;
		Button _play;
		Button _option;
		Button _escape; 
		irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;
		irr::video::ITexture *_title;
		irr::scene::IParticleSystemSceneNode* _particleSystem;
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
		sf::Sound _select;
		sf::SoundBuffer _buffer2;
		int32_t _nbSound = 25;
};

#endif /* !MENU_HPP_ */
