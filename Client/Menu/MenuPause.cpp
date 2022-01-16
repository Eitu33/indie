/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuPause
*/

#include "MenuPause.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include "Button.hpp"
#include "driverChoice.h"
#include "SFML/Audio.hpp"

MenuPause::MenuPause(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
    : _event(event), _device(device), _driver(driver), _sceneManager(sceneManager)
{
    _isPressed = false;
}

void MenuPause::initSprite(irr::gui::IGUIEnvironment *env)
{
    env->addImage(_driver->getTexture("pause.png"), irr::core::position2d<int>(550, 150));
}

void MenuPause::initButton(Button *resume, Button *option, Button *menu)
{
    const char *resume_1 = "resume_1.png";
    const char *resume_2 = "resume_2.png";
    const char *option_1 = "option_pause_1.png";
    const char *option_2 = "options_pause.png";
    const char *menu_1 = "menu_1.png";
    const char *menu_2 = "menu.png";
    
    resume->initButton(resume_1, resume_2, resume_2);
    option->initButton(option_1, option_2, option_2);
    menu->initButton(menu_1, menu_2, menu_2);
}

void MenuPause::subIndex()
{
    if (_index != 0)
        _index--;
    else
        _index = 2;
}

void MenuPause::addIndex()
{
    if (_index != 2)
        _index++;
    else
        _index = 0;
}

void MenuPause::checkChoice(irr::gui::IGUIEnvironment *env)
{
    if (_index == RESUME) {
        _choice = PauseKey::backGame;
        _run = false;
    } else if (_index == OPTION)  {
        _choice = PauseKey::menuOption;
        _run = false;
    } else if (_index == MENU) {
        _choice = PauseKey::mainMenu;
        _run = false;
    }
}

void MenuPause::checkInput(irr::gui::IGUIEnvironment *env)
{
    if (_event->IsKeyDown(irr::KEY_RIGHT)) {
        if (_isPressed == false) {
            _isPressed = true;
            subIndex();
        }
    } else if (_event->IsKeyDown(irr::KEY_LEFT)) {
        if (_isPressed == false) {
            _isPressed = true;
            addIndex();
        }
    } else if (_event->IsKeyDown(irr::KEY_RETURN)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
        }
    } else if (_isReleased == true && _isPressed == false) {
        checkChoice(env);
        _isReleased = false;
    } else
        _isPressed = false;
}

void MenuPause::printButton(irr::gui::IGUIEnvironment *env, Button *resume, Button *option, Button *menu)
{
    if (_index == RESUME) {
        resume->drawButton(env, 180, 350, 1);
        option->drawButton(env, 600, 349, 0);
        menu->drawButton(env, 1020, 350, 0);
    } else if (_index == OPTION) {
        resume->drawButton(env, 180, 350, 0);
        option->drawButton(env, 600, 349, 1);
        menu->drawButton(env, 1020, 350, 0);
    } else if (_index == MENU) {
        resume->drawButton(env, 180, 350, 0);
        option->drawButton(env, 600, 349, 0);
        menu->drawButton(env, 1020, 350, 1);
    }
}

void MenuPause::initCam()
{
    irr::scene::ICameraSceneNode *camera;
    irr::core::vector3df posCam;

    camera = _sceneManager->addCameraSceneNodeFPS (0,0,0, -1, NULL, 0, false, 0);
    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 20.0f, 0.0f));
}

void MenuPause::initParticle()
{
    _particleSystem =
    _sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* emitter = _particleSystem->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),                         // coordonnees de la boite
    irr::core::vector3df(0.0f,0.3f,0.0f),                               // direction de diffusion
    1,50,                                                               // nb particules emises a la sec min / max
    irr::video::SColor(0, 255, 0, 0),                                   // couleur la plus sombre
    irr::video::SColor(0, 255, 200, 0),                                 // couleur la plus claire
    600, 2000,                                                          // duree de vie min / max
    360,                                                                // angle max d'ecart / direction prevue
    irr::core::dimension2df(6.0f,6.0f),                                 // taille minimum
    irr::core::dimension2df(20.0f,20.0f));                              // taille maximum

    _particleSystem->setEmitter(emitter);                                // on attache l'emetteur
    emitter->drop();                                                    // plus besoin de ca
    _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);   // insensible a la lumiere
}

MenuPause::PauseKey MenuPause::getChoice()
{
    return (_choice);
}

void MenuPause::menuLoop()
{
    irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();
    env->clear();
    Button resume(_device, _driver, _sceneManager);
    Button option(_device, _driver, _sceneManager);
    Button menu(_device, _driver, _sceneManager);
    
    initButton(&resume, &option, &menu);
    initSprite(env);
    _device->getCursorControl ()-> setVisible (false);
    initCam();
    initParticle();
    while (_device->run() && _driver && _run == true) {
        checkInput(env);
        if (_device->isWindowActive()) {
            _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
            printButton(env, &resume, &option, &menu);
            _sceneManager->drawAll();
            env->drawAll();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            _driver->endScene();
        }
    }
    _particleSystem->remove();
}