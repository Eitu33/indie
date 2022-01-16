/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Button.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include "driverChoice.h"

MenuMode::MenuMode(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager, int32_t sound)
: _event(event), _device(device), _driver(driver), _sceneManager(sceneManager), 
_classic(device, driver, sceneManager), _tournament(device, driver, sceneManager), _nbSound(sound) 
{
    initButton();
    loadSound();
}

void MenuMode::initSprite(irr::gui::IGUIEnvironment *env)
{
    env->addImage(_driver->getTexture("titre_mode.png"), irr::core::position2d<int>(150, 150));
}

void MenuMode::initButton()
{
    _classic.initButton("classic_1.png", "classic_2.png", "classic_2.png");
    _tournament.initButton("tournament_1.png", "tournament_2.png", "tournament_2.png");
}

void MenuMode::subIndex()
{
    if (_index != 0)
        _index--;
    else
        _index = 1;
}

void MenuMode::addIndex()
{
    if (_index != 1)
        _index++;
    else
        _index = 0;
}

void MenuMode::goMenuSave(irr::gui::IGUIEnvironment *env) 
{
    MenuSave menuSave(_event, _device, _driver, _sceneManager, _nbSound);
    menuSave.menuLoop();
    _gameIsNew = menuSave.getGameIsNew();
    _nbPlayer = menuSave.getNbPlayer();
    if (menuSave._goGame == true) {
        _goGame = true;
        _run =false;
    } else 
        initSprite(env);
}

void MenuMode::checkChoice(irr::gui::IGUIEnvironment *env)
{
    if (_index == CLASSIC) {
        _gameMode = CLASSIC;
        goMenuSave(env);
    } else if (_index == TOURNAMENT)
        _gameMode = TOURNAMENT;
}

void MenuMode::checkInput(irr::gui::IGUIEnvironment *env)
{
    if (_event->IsKeyDown(irr::KEY_RIGHT)) {
        if (_isPressed == false) {
            _isPressed = true;
            subIndex();
        }
        _sound.play();
    } else if (_event->IsKeyDown(irr::KEY_LEFT)) {
        if (_isPressed == false) {
            _isPressed = true;
            addIndex();
        }
        _sound.play();
    } else if (_event->IsKeyDown(irr::KEY_RETURN)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
        }
        _select.play();
    } else if (_isReleased == true && _isPressed == false) {
        checkChoice(env);
        _isReleased = false;
    
    } else if (_event->IsKeyDown(irr::KEY_ESCAPE)) {
        if (_isPressed == false) {
            _isPressed = true;
            _run = false;
        }
    } else
        _isPressed = false;
}

void MenuMode::printButton(irr::gui::IGUIEnvironment *env)
{
    if (_index == CLASSIC) {
        _classic.drawButton(env, 300, 350, 1);
        _tournament.drawButton(env, 880, 349, 0);
    } else if (_index == TOURNAMENT) {
        _classic.drawButton(env, 300, 350, 0);
        _tournament.drawButton(env, 880, 349, 1);
    }
}

void MenuMode::initCam()
{
    irr::scene::ICameraSceneNode *camera;
    irr::core::vector3df posCam;

    camera = _sceneManager->addCameraSceneNodeFPS (0,0,0, -1, NULL, 0, false, 0);
    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 20.0f, 0.0f));
}

void MenuMode::initParticle()
{
    irr::scene::IParticleSystemSceneNode* particleSystem =
    _sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* emitter = particleSystem->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
    irr::core::vector3df(0.0f,0.3f,0.0f),
    1,50,                                                               // nb particules emises a la sec min / max
    irr::video::SColor(0, 255, 0, 0),                                   // couleur la plus sombre
    irr::video::SColor(0, 255, 200, 0),                                 // couleur la plus claire
    600, 2000,                                                          // duree de vie min / max
    360,                                                                // angle max d'ecart / direction prevue
    irr::core::dimension2df(6.0f,6.0f),                                 // taille minimum
    irr::core::dimension2df(20.0f,20.0f));                              // taille maximum

    particleSystem->setEmitter(emitter);
    emitter->drop();
    particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void MenuMode::initLoop(irr::gui::IGUIEnvironment *env)
{
    env->clear();
    initSprite(env);
    _device->getCursorControl ()-> setVisible(false);
    initCam();
    initParticle();
}

void MenuMode::drawLoop(irr::gui::IGUIEnvironment *env)
{
    _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
    printButton(env);
    _sceneManager->drawAll();
    env->drawAll();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    _driver->endScene();
}

void MenuMode::menuLoop()
{
    irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();

    initLoop(env);
    while (_device->run() && _driver && _run == true) {
        checkInput(env);
        if (_device->isWindowActive())
            drawLoop(env);
        if (_gameMode == TOURNAMENT)
            break;
    }
    env->clear();
}

void MenuMode::loadSound()
{
    if (!_buffer.loadFromFile("button.ogg")) {
        throw std::exception();
    }
     if (!_buffer2.loadFromFile("select.ogg")) {
        throw std::exception();
    }
    _sound.setBuffer(_buffer);
    _select.setBuffer(_buffer2);
    _sound.setVolume(_nbSound);
    _select.setVolume(_nbSound);
}

int32_t MenuMode::getNbPlayer()
{
    return (_nbPlayer);
}

bool MenuMode::getGameIsNew()
{
    return (_gameIsNew);
}

int32_t MenuMode::getGameMode()
{
    return (_gameMode);
}