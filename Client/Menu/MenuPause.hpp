/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuPause
*/

#ifndef MENUPAUSE_HPP_
#define MENUPAUSE_HPP_
#define RESUME 2
#define OPTION 1
#define MENU 0

#include <stdbool.h>
#include "irrlicht.h"
#include "Event.hpp"
#include "Button.hpp"
#include "Client.hpp"
#include "PauseKey.hpp"
#include "SFML/Audio.hpp"

class MenuPause {
	public:
    	enum class PauseKey {
	    	backGame = 0,
        	menuOption = 1,
        	mainMenu = 2,
    	};
		MenuPause(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager);
		~MenuPause() = default;
		void addIndex();
		void changeIndex();
		void checkChoice(irr::gui::IGUIEnvironment *env);
		void checkInput(irr::gui::IGUIEnvironment *env);
		void initButton(Button *resume, Button *option, Button *menu);
		void initCam();
		void initParticle();
		void initSprite(irr::gui::IGUIEnvironment *env);
		void menuLoop();
		void printButton(irr::gui::IGUIEnvironment *env, Button *resume, Button *option, Button *menu);
		void subIndex();
		
		PauseKey getChoice();		

	protected:
	private:
        	PauseKey _choice;
		Event *_event;
		bool _isPressed = false;
		int32_t _index = 2;
		bool _isReleased = false;
		bool _isChoose = false;
		bool _run = true;
    		irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;
		irr::video::ITexture *_title;
		irr::scene::IParticleSystemSceneNode* _particleSystem;

		sf::Sound _sound;
		sf::SoundBuffer _buffer;
};

#endif /* !MENUPAUSE_HPP_ */
