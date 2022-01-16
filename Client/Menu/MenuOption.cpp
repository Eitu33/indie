/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuOption
*/

#include "MenuOption.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include "Button.hpp"
#include "driverChoice.h"
#include "SFML/Audio.hpp"

MenuOption::MenuOption(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
    : _event(event), _device(device), _driver(driver), _sceneManager(sceneManager), _sound_1(device, driver, sceneManager), 
    _sound_2(device, driver, sceneManager), _fps_1(device, driver, sceneManager), _fps_2(device, driver, sceneManager), 
    _nbFps(device, driver, sceneManager), _nbSound(device, driver, sceneManager), _nbSound2(device, driver, sceneManager)
{
    _isPressed = false;
    initButton();
}

void MenuOption::initSprite(irr::gui::IGUIEnvironment *env)
{
    env->addImage(_driver->getTexture("titre_options.png"), irr::core::position2d<int>(570, 150));
}

void MenuOption::initButton()
{
    _sound_1.initButton("sound_1.png", "sound_2.png", "sound_2.png");
    _sound_2.initButton("sound_3.png", "sound_left.png", "sound_right.png");
    _fps_1.initButton("fps_1.png","fps_2.png", "fps_2.png");
    _fps_2.initButton("fps_3.png", "fps_left.png", "fps_right.png");
    _nbSound.initButton("sound_0.png", "sound_25.png", "sound_50.png");
    _nbSound2.initButton("sound_75.png", "sound_100.png", "sound_100.png");
    _nbFps.initButton("fps_30.png", "fps_60.png", "fps_90.png");
}

void MenuOption::subIndex()
{
    if (_index != 0)
        _index--;
    else
        _index = 1;
}

void MenuOption::addIndex()
{
    if (_index != 1)
        _index++;
    else
        _index = 0;
}

void MenuOption::checkChoice(irr::gui::IGUIEnvironment *env)
{
    if (_index == SOUND && _option == -1)
        _option = SOUND;
    else if (_index == FPS && _option == -1)
        _option = FPS;
}

void MenuOption::subSound()
{
    if (_sound != 0)
        _sound -= 25;
}

void MenuOption::addSound()
{
    if (_sound != 100)
        _sound += 25;
}

void MenuOption::subFps()
{
    if (_fps != 30)
        _fps -= 30;
}

void MenuOption::addFps()
{
    if (_fps != 90)
        _fps += 30;
}

void MenuOption::checkNoOption(irr::gui::IGUIEnvironment *env)
{
    if (_event->IsKeyDown(irr::KEY_RIGHT) && _option == -1) {
        if (_isPressed == false) {
            _isPressed = true;
            subIndex();
        }
    } else if (_event->IsKeyDown(irr::KEY_LEFT) && _option == -1) {
        if (_isPressed == false) {
            _isPressed = true;
            addIndex();
        }
    } else if (_event->IsKeyDown(irr::KEY_RETURN) && _option == -1) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _enter = true;
        }
    } else if (_isReleased == true && _isPressed == false && _enter == true) {
        checkChoice(env);
        _isReleased = false;
        _enter = false;
    } else
        _isPressed = false;
}

void MenuOption::releaseSoundManager()
{
    if (_left == true && _option == SOUND) {
        subSound();
        _music.setVolume(_sound);
        _left = false;
    } else if (_right == true && _option == SOUND) {
        addSound();
        _music.setVolume(_sound);
        _right = false;
    }
}

void MenuOption::releaseFpsManager()
{
    if (_left == true && _option == FPS) {
        subFps();
        _left = false;
    } else if (_right == true && _option == FPS) {
        addFps();
        _right = false;
    }
}

void MenuOption::releaseEnterManager(irr::gui::IGUIEnvironment *env)
{
    if (_enter == true) {
        _option = -1;
        env->clear();
        _enter = false;
        initSprite(env);
    }
}

void MenuOption::checkSoundOption(irr::gui::IGUIEnvironment *env)
{
    if (_event->IsKeyDown(irr::KEY_LEFT) && (_option == SOUND || _option == FPS)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _left = true;
        }
    } else if (_event->IsKeyDown(irr::KEY_RIGHT) && (_option == SOUND || _option == FPS)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _right = true;
        }
    } else if (_event->IsKeyDown(irr::KEY_RETURN) && (_option == SOUND || _option == FPS)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _enter = true;
    }
    } else if (_isReleased == true && _isPressed == false && (_option == SOUND || _option == FPS)) {
        releaseFpsManager();
        releaseSoundManager();
        releaseEnterManager(env);
    }
}

void MenuOption::checkInput(irr::gui::IGUIEnvironment *env)
{
    checkNoOption(env);
    checkSoundOption(env);
     if (_event->IsKeyDown(irr::KEY_ESCAPE)) {
         _run = false;
     } 
}

void MenuOption::printNbSound(irr::gui::IGUIEnvironment *env)
{
    if (_sound == 0)
        _nbSound.drawButton(env, 281, 655, 0);
    else if (_sound == 25)
        _nbSound.drawButton(env, 281, 655, 1);
    else if (_sound == 50)
        _nbSound.drawButton(env, 281, 655, 2);
    else if (_sound == 75)
        _nbSound2.drawButton(env, 281, 655, 0);
    else if (_sound == 100)
        _nbSound2.drawButton(env, 281, 655, 1);
}

void MenuOption::printNbFps(irr::gui::IGUIEnvironment *env)
{
    if (_fps == 30)
        _nbFps.drawButton(env, 900, 655, 0);
    else if (_fps == 60)
        _nbFps.drawButton(env, 900, 655, 1);
    else if (_fps == 90)
        _nbFps.drawButton(env, 900, 655, 2);
}

void MenuOption::printSoundButton(irr::gui::IGUIEnvironment *env)
{
    if (_index == SOUND && _option == SOUND && _left == true) {
        _sound_2.drawButton(env, 200, 345, 1);
        _fps_1.drawButton(env, 900, 349, 0);
    } else if (_index == SOUND && _option == SOUND && _right == true) {
        _sound_2.drawButton(env, 200, 345, 2);
        _fps_1.drawButton(env, 900, 349, 0);
    }  else if (_index == SOUND && _option == SOUND && _right == false && _left == false) {
        _sound_2.drawButton(env, 200, 345, 0);
        _fps_1.drawButton(env, 900, 349, 0);
    }
}

void MenuOption::printFpsButton(irr::gui::IGUIEnvironment *env)
{
    if (_index == FPS && _option == FPS && _left == true) {
        _sound_1.drawButton(env, 280, 350, 0);
        _fps_2.drawButton(env, 820, 345, 1);
    } else if (_index == FPS && _option == FPS && _right == true) {
        _sound_1.drawButton(env, 280, 350, 0);
        _fps_2.drawButton(env, 820, 345, 2);
    }  else if (_index == FPS && _option == FPS && _right == false && _left == false) {
        _sound_1.drawButton(env, 280, 350, 0);
        _fps_2.drawButton(env, 820, 345, 0);
    }
}

void MenuOption::printSimpleButton(irr::gui::IGUIEnvironment *env)
{
    if (_index == SOUND & _option == -1) {
        _sound_1.drawButton(env, 280, 350, 1);
        _fps_1.drawButton(env, 900, 350, 0);
    } else if (_index == FPS && _option == -1) {
        _sound_1.drawButton(env, 280, 350, 0);
        _fps_1.drawButton(env, 900, 350, 1);
    }
}

void MenuOption::printButton(irr::gui::IGUIEnvironment *env)
{
    printSimpleButton(env);
    printSoundButton(env);
    printFpsButton(env);
    if (_option == SOUND)
        printNbSound(env);
    else if (_option == FPS)
        printNbFps(env);
}

void MenuOption::initCam()
{
    irr::scene::ICameraSceneNode *camera;
    irr::core::vector3df posCam;

    camera = _sceneManager->addCameraSceneNodeFPS (0,0,0, -1, NULL, 0, false, 0);
    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 20.0f, 0.0f));
}

void MenuOption::initParticle()
{
    _particleSystem =
    _sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* emitter = _particleSystem->createBoxEmitter (
    irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
    irr::core::vector3df(0.0f,0.3f,0.0f),
    1,50,
    irr::video::SColor(0, 255, 0, 0),
    irr::video::SColor(0, 255, 200, 0),
    600, 2000,
    360,
    irr::core::dimension2df(6.0f,6.0f),
    irr::core::dimension2df(20.0f,20.0f));

    _particleSystem->setEmitter(emitter);
    emitter->drop();
    _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void MenuOption::initLoop(irr::gui::IGUIEnvironment *env) 
{
    env->clear();
    initSprite(env);
    loadMusic();
    _device->getCursorControl ()-> setVisible (false);
    initCam();
    initParticle();
}

void MenuOption::drawLoop(irr::gui::IGUIEnvironment *env)
{
    _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
    printButton(env);
    _sceneManager->drawAll();
    env->drawAll();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    _driver->endScene();
}

void MenuOption::loadMusic()
{
    if (!_music.openFromFile("music.ogg"))
        throw std::exception();
    _music.play();
}


// void Menu::loadSound()
// {
//     if (!_buffer.loadFromFile("button.ogg")) {
//         throw std::exception();
//     }
//     _sound.setBuffer(_buffer);
// }

void MenuOption::menuLoop()
{
    irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();

    initLoop(env);
    while (_device->run() && _driver && _run == true) {
        checkInput(env);
        if (_device->isWindowActive())
            drawLoop(env);
    }
     env->clear();
}
