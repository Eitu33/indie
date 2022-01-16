/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "irrlicht.h"
#include <iostream>

class Button {
	public:
		Button(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager);
		~Button() = default;
        void initButton(const char *pathOne, const char *pathTwo, const char *pathThree);
        void drawButton(irr::gui::IGUIEnvironment* env, int x, int y, uint32_t state);
        bool _activation = false;

    protected:
    private:
        int state;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_sceneManager;
        irr::video::ITexture *_stateOne;
        irr::video::ITexture *_stateTwo;
        irr::video::ITexture *_stateThree;
};

#endif /* !BUTTON_HPP_ */
