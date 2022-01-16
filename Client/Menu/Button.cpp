/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
:_device(device), _driver(driver), _sceneManager(sceneManager) {}

void Button::initButton(const char *pathOne, const char *pathTwo, const char *pathThree)
{
    _stateOne = _driver->getTexture(pathOne);
    _stateTwo = _driver->getTexture(pathTwo);
    _stateThree = _driver->getTexture(pathThree);
    if (!_stateOne || !_stateTwo || !_stateThree) {
        throw std::exception();
    }
}

void Button::drawButton(irr::gui::IGUIEnvironment* env, int x, int y, uint32_t state)
{
    if (state == 0) {
        env->addImage(_stateOne, irr::core::position2d<int>(x, y));
    }
    if (state == 1) {
        env->addImage(_stateTwo, irr::core::position2d<int>(x, y));
    }
    if (state == 2) {
        env->addImage(_stateThree, irr::core::position2d<int>(x, y));
    }
}