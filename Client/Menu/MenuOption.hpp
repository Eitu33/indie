/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuOption
*/

#ifndef MENUOPTION_HPP_
#define MENUOPTION_HPP_

#define SOUND 0
#define FPS 1
#define NOOPTION -1;

#include <stdbool.h>
#include "irrlicht.h"
#include "Event.hpp"
#include "Button.hpp"
#include "Client.hpp"
#include "SFML/Audio.hpp"

class MenuOption {
	public:
		MenuOption(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager);
		~MenuOption() = default;
		void changeIndex();
		void checkChoice(irr::gui::IGUIEnvironment *env);
		void checkInput(irr::gui::IGUIEnvironment *env);
		void initButton();
		void initCam();
		void initParticle();
		void initSprite(irr::gui::IGUIEnvironment *env);
		void menuLoop();
		void printButton(irr::gui::IGUIEnvironment *env);
        void initLoop(irr::gui::IGUIEnvironment *env);
        void drawLoop(irr::gui::IGUIEnvironment *env);
        void checkNoOption(irr::gui::IGUIEnvironment *env);
        void checkSoundOption(irr::gui::IGUIEnvironment *env);
        void checkFpsOption(irr::gui::IGUIEnvironment *env);
        void printNbSound(irr::gui::IGUIEnvironment *env);
        void printSimpleButton(irr::gui::IGUIEnvironment *env);
        void printFpsButton(irr::gui::IGUIEnvironment *env);
        void printSoundButton(irr::gui::IGUIEnvironment *env);
        void printNbFps(irr::gui::IGUIEnvironment *env);
        void releaseSoundManager();
        void releaseFpsManager();
        void releaseEnterManager(irr::gui::IGUIEnvironment *env);
        void loadMusic();
        void addIndex();
        void subIndex();
        void subSound();
        void addSound();
        void addFps();
        void subFps();
        int32_t _sound = 25;

	protected:
	private:
		Event *_event;
		bool _isPressed = false;
        bool _isReleased = false;
		bool _isChoose = false;
		bool _run = true;
        bool _left = false;
        bool _right = false;
        bool _enter = false;
		int32_t _index = 0;
        int32_t _fps = 60;
        int32_t _option = -1;
        sf::Music _music;
        irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_sceneManager;
		irr::video::ITexture *_title;
		irr::scene::IParticleSystemSceneNode* _particleSystem;
        Button _sound_1;
        Button _sound_2;
        Button _fps_1;
        Button _fps_2;
        Button _nbFps;
        Button _nbSound;
        Button _nbSound2;

		sf::Sound _soundButton;
		sf::SoundBuffer _buffer;
};

#endif /* !MENUOPTION_HPP_ */
