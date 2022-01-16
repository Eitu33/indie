/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuSave
*/

#ifndef MENUSAVE_HPP_
#define MENUSAVE_HPP_

#define NOCHOICE -1
#define NEW 0
#define LOAD 1

#include <stdbool.h>
#include "irrlicht.h"
#include "Event.hpp"
#include "Button.hpp"
#include "MenuMode.hpp"
#include "Client.hpp"
#include "SFML/Audio.hpp"

class MenuSave {
	public:
		MenuSave(Event *event, irr::IrrlichtDevice *device, 
		irr::video::IVideoDriver *driver, 
		irr::scene::ISceneManager *sceneManager, int32_t sound);
		~MenuSave() = default;
		void initSprite(irr::gui::IGUIEnvironment *env);
		void initButton();
		void subIndex();
		void addIndex();
		void checkChoice(irr::gui::IGUIEnvironment *env);
		void checkInput(irr::gui::IGUIEnvironment *env);
		void printButton(irr::gui::IGUIEnvironment *env);
		void initCam();
		void initParticle();
		int32_t getNbPlayer();
		void initLoop(irr::gui::IGUIEnvironment *env);
		void drawLoop(irr::gui::IGUIEnvironment *env);
		void menuLoop();
		bool _goGame = false;
		bool getGameIsNew();
		void goMenuNbPlayer(irr::gui::IGUIEnvironment *env);
		void loadSound();
		
	protected:
	private:
		int32_t _game = -1; 
		Event *_event;
		bool _isPressed = false;
		int32_t _index = 0;
		int32_t _nbPlayer = 0;
		bool _escape = false;
		bool _isReleased = false;
		bool _isChoose = false;
		bool _gameIsNew = false;
		bool _run = true;
		Button _newGame;
		Button _loadGame;
    	irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;
		irr::video::ITexture *_title;
		irr::scene::IParticleSystemSceneNode* _particleSystem;
		sf::Sound _sound;
		sf::SoundBuffer _buffer;
		sf::Sound _select;
		sf::SoundBuffer _buffer2;
		int32_t _nbSound;
};

#endif /* !MENUSAVE_HPP_ */
