/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
    : _event(event), _device(device), _driver(driver), _sceneManager(sceneManager), _play(device, driver, sceneManager),
    _option(device, driver, sceneManager), _escape(device, driver, sceneManager)
{
    initButton();
    loadMusic();
    loadSound();
}

void Menu::initSprite(irr::gui::IGUIEnvironment *env)
{
    if (env->addImage(_driver->getTexture("titre.png"), irr::core::position2d<int>(370, 150)) == 0) {
         throw std::exception();
    }
}

void Menu::initButton()
{
    _play.initButton("play_1.png", "play_2.png", "play_2.png");
    _option.initButton("option_1.png", "option_2.png", "option_2.png");
    _escape.initButton("escape_1.png", "escape_2.png", "escape_2.png");
}

void Menu::subIndex()
{
    if (_index != 0)
        _index--;
    else
        _index = 2;
}

void Menu::addIndex()
{
    if (_index != 2)
        _index++;
    else
        _index = 0;
}

void Menu::goModeMenu(irr::gui::IGUIEnvironment *env)
{
    MenuMode menuMode(_event, _device, _driver, _sceneManager, _nbSound);
    while (_sound.getStatus() != sf::Sound::Status::Stopped);
    menuMode.menuLoop();
    _gameMode = menuMode.getGameMode();
    _nbPlayer = menuMode.getNbPlayer();
    _gameIsNew = menuMode.getGameIsNew();
    if (menuMode._goGame == true)
        _run = false;
    else
        initSprite(env);
}

void Menu::goMenuOption(irr::gui::IGUIEnvironment *env)
{
    MenuOption menuOption(_event, _device, _driver, _sceneManager);
    _music.pause();
    while (_sound.getStatus() != sf::Sound::Status::Stopped);
    menuOption.menuLoop();
    _nbSound = menuOption._sound;
    _music.setVolume(menuOption._sound);
    _sound.setVolume(menuOption._sound);
    _select.setVolume(menuOption._sound);
    _music.play();
    initSprite(env);
}

void Menu::checkChoice(irr::gui::IGUIEnvironment *env)
{
    if (_index == PLAY)
        goModeMenu(env);
    else if (_index == OPTION)
        goMenuOption(env);
    else if (_index == EXIT) {
        _gameMode = -1;
        _run = false;
    }
}

void Menu::checkInput(irr::gui::IGUIEnvironment *env)
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
    } else
        _isPressed = false;

}

void Menu::printButton(irr::gui::IGUIEnvironment *env)
{
    if (_index == PLAY) {
        _play.drawButton(env, 180, 350, 1);
        _option.drawButton(env, 600, 349, 0);
        _escape.drawButton(env, 1020, 350, 0);
    } else if (_index == OPTION) {
        _play.drawButton(env, 180, 350, 0);
        _option.drawButton(env, 600, 349, 1);
        _escape.drawButton(env, 1020, 350, 0);
    } else if (_index == EXIT) {
        _play.drawButton(env, 180, 350, 0);
        _option.drawButton(env, 600, 349, 0);
        _escape.drawButton(env, 1020, 350, 1);
    }
}

int32_t Menu::getNbPlayer() 
{
    return (_nbPlayer);
}

void Menu::initCam()
{
    irr::scene::ICameraSceneNode *camera;
    irr::core::vector3df posCam;

    camera = _sceneManager->addCameraSceneNodeFPS (0,0,0, -1, NULL, 0, false, 0);
    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 20.0f, 0.0f));
}

void Menu::initParticle()
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

void Menu::initLoop(irr::gui::IGUIEnvironment *env)
{
    env->clear();
    initSprite(env);
    _device->getCursorControl()->setVisible (false);
    initCam();
    initParticle();
}

void Menu::loadMusic()
{
    if (!_music.openFromFile("music.ogg"))
        throw std::exception();
    _music.setVolume(_nbSound);
}

void Menu::loadSound()
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

void Menu::drawLoop(irr::gui::IGUIEnvironment *env)
{
    _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
    printButton(env);
    _sceneManager->drawAll();
    env->drawAll();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    _driver->endScene();
}

void Menu::menuLoop()
{
    _music.play();
    irr::gui::IGUIEnvironment *env = _device->getGUIEnvironment();
    initLoop(env);

    while (_device->run() && _driver && _run == true) {
        checkInput(env);
        if (_device->isWindowActive()) {
            drawLoop(env);
            if (_gameMode == TOURNAMENT) {
                break;
            }
        }
    }
    _sceneManager->clear();
    _music.stop();
    _sound.stop();
    _select.stop();
}

int32_t Menu::getGameMode()
{
    return (_gameMode);
}

bool Menu::getGameIsNew()
{
    return (_gameIsNew);
}

int32_t Menu::getNbSound()
{
    return (_nbSound);
}