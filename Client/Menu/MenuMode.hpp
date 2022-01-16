/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuMode
*/

#ifndef MENUMODE_HPP_
#define MENUMODE_HPP_
#define CLASSIC 1
#define TOURNAMENT 0
#define NOMODE -1

#include "irrlicht.h"
#include "Event.hpp"
#include "Button.hpp"
#include "MenuNbPlayer.hpp"
#include "SFML/Audio.hpp"
#include "MenuSave.hpp"

#include <stdbool.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "driverChoice.h"

class MenuMode {
		public:
		MenuMode(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager, int32_t sound);
		~MenuMode() = default;
		void addIndex();
		void changeIndex();
		void checkChoice(irr::gui::IGUIEnvironment *env);
		void checkInput(irr::gui::IGUIEnvironment *env);
		void initButton();
		void initCam();
		void initParticle();
		void initSprite(irr::gui::IGUIEnvironment *env);
		void goMenuSave(irr::gui::IGUIEnvironment *env);
		void menuLoop();
		void printButton(irr::gui::IGUIEnvironment *env);
		void subIndex();
		void goMenuNbPlayer(irr::gui::IGUIEnvironment *env); 
		void initLoop(irr::gui::IGUIEnvironment *env);
		void drawLoop(irr::gui::IGUIEnvironment *env);
		bool _goGame = false;
		void loadSound();
		int32_t getGameMode();
		int32_t getNbPlayer();
		bool getGameIsNew();

	protected:
	private:
		Event *_event;
		bool _isPressed = false;
		int32_t _index = 1;
		int32_t _gameMode = -1;
	;	bool _gameIsNew = false;
		int32_t _nbPlayer = 0;
		bool _isReleased = false;
		bool _isChoose = false;
		bool _run = true;
		Button _classic;
		Button _tournament;
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

#endif /* !MENUMODE_HPP_ */
