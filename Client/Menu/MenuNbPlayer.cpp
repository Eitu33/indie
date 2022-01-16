/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuNbPlayer
*/

#include "MenuNbPlayer.hpp"

MenuNbPlayer::MenuNbPlayer(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager, int32_t sound)
    : _event(event), _device(device), _driver(driver), _sceneManager(sceneManager), _nbSound(sound)
{
    _isPressed = false;
    loadSound();
}

void MenuNbPlayer::initSprite(irr::gui::IGUIEnvironment *env)
{
    env->addImage(_driver->getTexture("titre_nbplayer.png"), irr::core::position2d<int>(300, 150));
}

void MenuNbPlayer::initButton(Button *one, Button *two, Button *three, Button *four)
{
    one->initButton("player_1.png", "player_1.png", "player_1.png");
    two->initButton("add_player.png", "player_2.png", "player_2.png");
    three->initButton("add_player.png", "player_3.png", "player_3.png");
    four->initButton("add_player.png", "player_4.png", "player_4.png");
}

void MenuNbPlayer::subIndex()
{
    if (_index != 1)
        _index--;
}

void MenuNbPlayer::addIndex()
{
    if (_index != 3)
        _index++;
}

void MenuNbPlayer::updateNbPlayer(Button *button, int nb)
{
    if (button->_activation == false && _keyIsPressed != CLEAR) {
        button->_activation = true;
        _nbPlayer = nb;
    } else if (button->_activation == true && _keyIsPressed == CLEAR) {
        button->_activation = false;
        _nbPlayer = nb - 1;
    }
}

void MenuNbPlayer::checkChoice(irr::gui::IGUIEnvironment *env, Button *one, Button *two, Button *three, Button *four)
{
    if (_index == ONE)
        updateNbPlayer(one, 1);
    else if (_index == TWO)
        updateNbPlayer(two, 2);
    else if (_index == THREE)
        updateNbPlayer(three, 3);
    else if (_index == FOUR) {
        updateNbPlayer(four, 4);
    }
}

int32_t MenuNbPlayer::getNbPlayer() 
{
    return (_nbPlayer);
}

void MenuNbPlayer::pressManager(int key)
{
    if (_isPressed == false) {
        _isPressed = true;
        _isReleased = true;
        _keyIsPressed = key;
    }
}

void MenuNbPlayer::checkInput(irr::gui::IGUIEnvironment *env, Button *one, Button *two, Button *three, Button *four)
{
    if (_event->IsKeyDown(irr::KEY_SPACE)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _keyIsPressed = SPACE;
        }
        _sound.play();
    } else if (_event->IsKeyDown(irr::KEY_BACK)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _keyIsPressed = CLEAR;
        }
        _sound.play();
    } else if (_event->IsKeyDown(irr::KEY_RETURN)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _keyIsPressed = ENTER;
        }
        _select.play();
    } else if (_event->IsKeyDown(irr::KEY_ESCAPE)) {
        if (_isPressed == false) {
            _isPressed = true;
            _isReleased = true;
            _keyIsPressed = ESC;
        }
    } else if (_isReleased == true && _isPressed == false && _keyIsPressed == ESC) {
        _run = false;
        _isReleased = false;
    } else if (_isReleased == true && _isPressed == false && _keyIsPressed == ENTER) {
        _run = false;
        _goGame = true; 
        _isReleased = false;
    } else if (_isReleased == true && _isPressed == false && _keyIsPressed == SPACE) {
        checkChoice(env, one, two, three, four);
        _isReleased = false;
        addIndex();
    } else if (_isReleased == true && _isPressed == false && _keyIsPressed == CLEAR) {
        checkChoice(env, one, two, three, four);
        _isReleased = false;
        subIndex();
    } else
        _isPressed = false;
}

void MenuNbPlayer::printButton(irr::gui::IGUIEnvironment *env, Button *one, Button *two, Button *three, Button *four)
{
    if (one->_activation == true)
        one->drawButton(env, 80, 350, 1);
    else
        one->drawButton(env, 80, 350, 0);
    if (two->_activation == true)
        two->drawButton(env, 430, 349, 1);
    else
        two->drawButton(env, 430, 349, 0);
    if (three->_activation == true)
        three->drawButton(env, 780, 350, 1);
    else
        three->drawButton(env, 780, 350, 0);
    if (four->_activation == true)
        four->drawButton(env, 1130, 350, 1);
    else
        four->drawButton(env, 1130, 350, 0);
}

void MenuNbPlayer::initCam()
{
    irr::scene::ICameraSceneNode *camera;
    irr::core::vector3df posCam;

    camera = _sceneManager->addCameraSceneNodeFPS (0,0,0, -1, NULL, 0, false, 0);
    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 20.0f, 0.0f));
}

void MenuNbPlayer::initParticle()
{
    irr::scene::IParticleSystemSceneNode* particleSystem =
    _sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* emitter = particleSystem->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),                         // coordonnees de la boite
    irr::core::vector3df(0.0f,0.3f,0.0f),                               // direction de diffusion
    1,50,                                                               // nb particules emises a la sec min / max
    irr::video::SColor(0, 255, 0, 0),                                   // couleur la plus sombre
    irr::video::SColor(0, 255, 200, 0),                                 // couleur la plus claire
    600, 2000,                                                          // duree de vie min / max
    360,                                                                // angle max d'ecart / direction prevue
    irr::core::dimension2df(6.0f,6.0f),                                 // taille minimum
    irr::core::dimension2df(20.0f,20.0f));                              // taille maximum

    particleSystem->setEmitter(emitter);                                // on attache l'emetteur
    emitter->drop();                                                    // plus besoin de ca
    particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);   // insensible a la lumiere
}

void MenuNbPlayer::loadSound()
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

void MenuNbPlayer::menuLoop()
{
    irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();
    env->clear();
    Button one(_device, _driver, _sceneManager);
    Button two(_device, _driver, _sceneManager);
    Button three(_device, _driver, _sceneManager);
    Button four(_device, _driver, _sceneManager);

    initButton(&one, &two, &three, &four);
    initSprite(env);
    _device->getCursorControl ()-> setVisible (false);
    initCam();
    initParticle();
    while (_device->run() && _driver && _run == true)
    {
        checkInput(env,& one, &two , &three, &four);
        if (_device->isWindowActive())
        {
            _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
            printButton(env, &one, &two, &three, &four);
            _sceneManager->drawAll();
            env->drawAll();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            _driver->endScene();
        }
    }
    env->clear();
}