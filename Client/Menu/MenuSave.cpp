/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** MenuSave
*/

#include "MenuSave.hpp"

MenuSave::MenuSave(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager, int32_t sound)
: _event(event), _device(device), _driver(driver), _sceneManager(sceneManager), _newGame(device, driver, sceneManager), _loadGame(device, driver, sceneManager),
_nbSound(sound)
{
    initButton();
    loadSound();
}

void MenuSave::initSprite(irr::gui::IGUIEnvironment *env)
{
    env->addImage(_driver->getTexture("game.png"), irr::core::position2d<int>(600, 150));
}

void MenuSave::initButton()
{
    _newGame.initButton("new_game.png", "new_game_2.png", "new_game_2.png");
    _loadGame.initButton("load_game.png", "load_game_2.png", "new_game_2.png");
}

void MenuSave::subIndex()
{
    if (_index != 0)
        _index--;
    else
        _index = 1;
}

void MenuSave::addIndex()
{
    if (_index != 1)
        _index++;
    else
        _index = 0;
}

void MenuSave::goMenuNbPlayer(irr::gui::IGUIEnvironment *env) 
{
    MenuNbPlayer menuNbPlayer(_event, _device, _driver, _sceneManager, _nbSound);
    menuNbPlayer.menuLoop();
    _nbPlayer = menuNbPlayer.getNbPlayer();
    if (menuNbPlayer._goGame == true) {
        _goGame = true;
        _run = false;
    } else 
        initSprite(env);
}

void MenuSave::checkChoice(irr::gui::IGUIEnvironment *env)
{
    if (_index == NEW)
        _gameIsNew = true;
    else if (_index == LOAD)
        _gameIsNew = false;
    goMenuNbPlayer(env);
}

void MenuSave::checkInput(irr::gui::IGUIEnvironment *env)
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
    } else if (_event->IsKeyDown(irr::KEY_ESCAPE)) {
        if (_isPressed == false) {
            _isPressed = true;
            _escape = true;
            _isReleased = true;
        }
    } else if (_isReleased == true && _isPressed == false && _escape == false) {
        checkChoice(env);
        _isReleased = false;
    } else if (_isReleased == true && _isPressed == false && _escape == true) {
        _run = false;
        _isReleased = false;
        _escape = false;
    } else
        _isPressed = false;
}

void MenuSave::printButton(irr::gui::IGUIEnvironment *env)
{
    if (_index == NEW) {
        _newGame.drawButton(env, 300, 350, 1);
        _loadGame.drawButton(env, 880, 349, 0);
    } else if (_index == LOAD) {
        _newGame.drawButton(env, 300, 350, 0);
        _loadGame.drawButton(env, 880, 349, 1);
    }
}

void MenuSave::initCam()
{
    irr::scene::ICameraSceneNode *camera;
    irr::core::vector3df posCam;

    camera = _sceneManager->addCameraSceneNodeFPS (0,0,0, -1, NULL, 0, false, 0);
    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 20.0f, 0.0f));
}

void MenuSave::initParticle()
{
    _particleSystem =
    _sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* emitter = _particleSystem->createBoxEmitter(
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

void MenuSave::loadSound()
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

int32_t MenuSave::getNbPlayer() 
{
    return (_nbPlayer);
}

void MenuSave::initLoop(irr::gui::IGUIEnvironment *env)
{
    initSprite(env);
    _device->getCursorControl ()-> setVisible (false);
    initCam();
    initParticle();
}

void MenuSave::drawLoop(irr::gui::IGUIEnvironment *env)
{
    _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
    printButton(env);
    _sceneManager->drawAll();
    env->drawAll();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    _driver->endScene();
}

void MenuSave::menuLoop()
{
    irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();

    env->clear();
    initLoop(env);
    while (_device->run() && _driver && _run == true) {
        checkInput(env);
        if (_device->isWindowActive())
            drawLoop(env);
    }
    env->clear();
}

bool MenuSave::getGameIsNew()
{
    return (_gameIsNew);
}