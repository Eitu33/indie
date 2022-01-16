/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** InGame
*/

#include "InGame.hpp"
#include <thread>
#include <chrono>

InGame::InGame(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
		std::shared_ptr<IClient> client)
    : Scene(event, device, driver, sceneManager, client)
{
	sf::SoundBuffer	explo;
	if (!explo.loadFromFile("explosion.ogg")) {
		throw;
	}
	_buffer.push_back(explo);

	sf::SoundBuffer	bonus;
	if (!explo.loadFromFile("Bonus.ogg")) {
		throw;
	}
	_buffer.push_back(bonus);
}

void InGame::displayPlayers()
{
}

void InGame::initGame(game_logic::GameData gameData)
{
	char *textures[4] = {(char *)"Red", (char *)"White", (char *)"Black", (char *)"Pink"};
	int i = 0;

	for (auto it = gameData.walls.begin(); it != gameData.walls.end(); it++) {
		struct Walls newWall = {irr::core::vector3df((*it).x, 0.0f, (*it).y), (*it).isBonus, (*it).isTough};
		newWall.node = _sceneManager->addCubeSceneNode(50.0f, 0, -1, newWall.pos);
		newWall.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		if (newWall.isTough)
			newWall.node->setMaterialTexture(0, _driver->getTexture("Box_undestroyable.jpeg"));
		else
			newWall.node->setMaterialTexture(0, _driver->getTexture("Box_destroyable.png"));
		_walls.push_back(newWall);
	}

	auto mesh = _sceneManager->getMesh("Bomberman.MD3");

	for (auto it = gameData.players.begin(); it != gameData.players.end(); it++) {
		struct Players newPlayer = {irr::core::vector3df((*it).x, 0.0f, (*it).y), (*it).id, (*it).isAlive};
		newPlayer.node = _sceneManager->addAnimatedMeshSceneNode(mesh, 0, -1, irr::core::vector3df((*it).x, 0.0f, (*it).y));
		newPlayer.node->setMaterialFlag(EMF_LIGHTING, false);
		newPlayer.node->setFrameLoop(27, 76);
		if (_client->isLocal())
			newPlayer.node->setMaterialTexture( 0, _driver->getTexture(std::string( std::string(textures[it->id]) + std::string("BombermanTextures.png")).c_str()));
		else
			if ((*it).id == _client->getID())
				newPlayer.node->setMaterialTexture( 0, _driver->getTexture(std::string( std::string(textures[2]) + std::string("BombermanTextures.png")).c_str()));
			else
				newPlayer.node->setMaterialTexture( 0, _driver->getTexture(std::string( std::string(textures[1]) + std::string("BombermanTextures.png")).c_str()));		
		newPlayer.node->setScale(vector3df(40, 40, 40));
		newPlayer.node->setRotation(vector3df(0, 0, 0));
    		newPlayer.node->setAnimationSpeed(30);
    		newPlayer.node->setLoopMode(true);
		newPlayer.isWalking = false;
		_players.push_back(newPlayer);
		i++;
	}
}

void InGame::changePlayerPostion(game_logic::GameData gameData)
{
	for(auto it = gameData.players.begin(); it != gameData.players.end(); it++) {
		auto player = std::find_if(_players.begin(), _players.end(), [&](struct Players const &playerTest) {
		return playerTest.id == (*it).id;});
		if (player == _players.end() || !player->isAlive)
			continue;
		irr::core::vector3df save = player->pos;
		if ((*it).x != player->node->getAbsolutePosition().X) {
			player->pos.X = (*it).x;
		}
		if ((*it).y != player->node->getAbsolutePosition().Z) {
			player->pos.Z = (*it).y;
		}
		player->node->setPosition(player->node->getAbsolutePosition() + irr::core::vector3df(player->pos.X - save.X, 0, player->pos.Z - save.Z));
		if ((*it).direction != game_logic::Direction::NONE) {
			if (!player->isWalking)
				player->node->setFrameLoop(0, 27);
			player->isWalking = true;
			switch ((*it).direction)
			{
			case game_logic::Direction::UP:
				player->node->setRotation(irr::core::vector3df(0, 0, 0));
				break;
			case game_logic::Direction::DOWN:
				player->node->setRotation(irr::core::vector3df(0, 180, 0));
				break;
			case game_logic::Direction::LEFT:
				player->node->setRotation(irr::core::vector3df(0, 90, 0));;
				break;
			case game_logic::Direction::RIGHT:
				player->node->setRotation(irr::core::vector3df(0, 270, 0));
				break;
			default:
				break;
			}
		}
		if (player->isWalking && (*it).direction == game_logic::Direction::NONE) {
			player->isWalking = false;
			player->node->setFrameLoop(27, 76);
		}
		if (player->isAlive && !(*it).isAlive) {
			player->isAlive = false;
			player->node->remove();
			player->node = 0;
		}
	}
}

void InGame::removeWall(irr::scene::IMeshSceneNode* explosion)
{
	auto wall = std::find_if(_walls.begin(), _walls.end(), [&](struct Walls const &wallsTest) {
	return wallsTest.pos == explosion->getAbsolutePosition();});
	if (wall != _walls.end()) {
		wall->node->remove();
		wall->node = 0;
		_walls.erase(wall);
	}
}


void InGame::manageBonus(game_logic::GameData gameData)
{
	char *textures[4] = {NULL, (char *)"BombPower.png", (char *)"SpeedBuff.png", (char *)"BombIcon.png"};

	for (auto it = gameData.walls.begin(); it != gameData.walls.end(); it++) {
		if ((*it).isBonus) {
			auto bonus = std::find_if(_bonus.begin(), _bonus.end(), [&](struct Walls const &wallsTest)  {
			return wallsTest.pos.X == (*it).x && wallsTest.pos.Z == (*it).y;});
			if (bonus == _bonus.end()) {
				struct Walls newWall = {irr::core::vector3df((*it).x, 0.0f, (*it).y), (*it).isBonus, (*it).isTough};
				newWall.node = _sceneManager->addCubeSceneNode(50.0f, 0, -1, newWall.pos);
				newWall.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				newWall.node->setMaterialTexture(0, _driver->getTexture(textures[(*it).bonus]));
				_bonus.push_back(newWall);
			}
		}
	}
	for (auto it = _bonus.begin(); it != _bonus.end();) {
		auto bonus = std::find_if(gameData.walls.begin(), gameData.walls.end(), [&](struct game_logic::WallData const &bonusTest) {
		return bonusTest.x == (*it).pos.X && bonusTest.y == (*it).pos.Z;});
		if (bonus == gameData.walls.end()) {
			sf::Sound *newSound = new sf::Sound;;
			newSound->setBuffer(_buffer[1]);
			newSound->play();
			_sounds.push_back(std::shared_ptr<sf::Sound>(newSound));
			(*it).node->remove();
			(*it).node = 0;
			it = _bonus.erase(it);
		} else {
			it++;
		}
	}
}

void InGame::manageBomb(game_logic::GameData gameData)
{
	auto mesh = _sceneManager->getMesh("Bomb.obj");
	for (auto it = gameData.bombs.begin(); it != gameData.bombs.end(); it++) {
		bool hasExploded = false;
		auto bomb = std::find_if(_bombs.begin(), _bombs.end(), [&](struct Bombs const &bombsTest) {
		return bombsTest.pos.X == (*it).x && bombsTest.pos.Z == (*it).y;});
		if (bomb == _bombs.end()) {
			struct Bombs newBomb = {irr::core::vector3df((*it).x, 0.0f, (*it).y)};
			newBomb.explosing = false;
			newBomb.node = _sceneManager->addAnimatedMeshSceneNode(mesh, 0, -1, irr::core::vector3df((*it).x, 0, (*it).y), irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10));
			newBomb.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			newBomb.node->setMaterialTexture( 0, _driver->getTexture("Bomb.png"));
			_bombs.push_back(newBomb);
			continue;
		}
		if ((*it).explosionSize[0] != -1 && !bomb->explosing) {
			irr::core::vector3df pos = bomb->node->getAbsolutePosition();
			irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1, pos);
			explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
			bomb->explosion.push_back(explosion);
			hasExploded = true;
			for (auto i = 0; (*it).explosionSize[0] != i; i++) {
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1,
				irr::core::vector3df(bomb->node->getAbsolutePosition().X, bomb->node->getAbsolutePosition().Y, bomb->node->getAbsolutePosition().Z - ((i + 1) * 50)));
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);
				removeWall(explosion);
			}
		}
		if ((*it).explosionSize[1] != -1 && !bomb->explosing) {
			if (!hasExploded) {
				irr::core::vector3df pos = bomb->node->getAbsolutePosition();
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1, pos);
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);				
			}
			hasExploded = true;
			for (auto i = 0; (*it).explosionSize[1] != i; i++) {
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1,
				irr::core::vector3df(bomb->node->getAbsolutePosition().X, bomb->node->getAbsolutePosition().Y, bomb->node->getAbsolutePosition().Z + ((i + 1) * 50)));
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);
				removeWall(explosion);
			}
		}
		if ((*it).explosionSize[2] != -1 && !bomb->explosing) {
			if (!hasExploded) {
				irr::core::vector3df pos = bomb->node->getAbsolutePosition();
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1, pos);
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);				
			}
			hasExploded = true;
			for (auto i = 0; (*it).explosionSize[2] != i; i++) {
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1,
				irr::core::vector3df(bomb->node->getAbsolutePosition().X - ((i + 1) * 50), bomb->node->getAbsolutePosition().Y, bomb->node->getAbsolutePosition().Z));
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);
				removeWall(explosion);
			}
		}
		if ((*it).explosionSize[3] != -1 && !bomb->explosing) {
			if (!hasExploded) {
				irr::core::vector3df pos = bomb->node->getAbsolutePosition();
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1, pos);
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);				
			}
			hasExploded = true;
			for (auto i = 0; (*it).explosionSize[3] != i; i++) {
				irr::scene::IMeshSceneNode *explosion = _sceneManager->addCubeSceneNode(50, 0, -1,
				irr::core::vector3df(bomb->node->getAbsolutePosition().X + ((i + 1) * 50), bomb->node->getAbsolutePosition().Y, bomb->node->getAbsolutePosition().Z));
				explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				explosion->setMaterialTexture( 0, _driver->getTexture("explosion.png"));
				bomb->explosion.push_back(explosion);
				removeWall(explosion);
			}
		}
		if (hasExploded) {
			bomb->explosing = true;
			bomb->node->remove();
			bomb->node = 0;
			sf::Sound *newSound = new sf::Sound;;
			newSound->setBuffer(_buffer[0]);
			newSound->play();
			_sounds.push_back(std::shared_ptr<sf::Sound>(newSound));
		}
	}
 	for (auto it = _bombs.begin(); it != _bombs.end();) {
		auto bomb = std::find_if(gameData.bombs.begin(), gameData.bombs.end(), [&](struct game_logic::BombData const &bombTest) {
		return bombTest.x == (*it).pos.X && bombTest.y == (*it).pos.Z;});
		if (bomb == gameData.bombs.end()) {
 			for (auto it2 = (*it).explosion.begin(); it2 != (*it).explosion.end(); it2++) {
				(*it2)->remove();
				(*it2) = 0;
			}
			it = _bombs.erase(it);
		} else
			it++;
	}
}

void InGame::run()
{
	game_logic::GameData gameData;
	if (firstTurn) {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		gameData = _client->getInfosInGame();
		_mapDisplayer.renderMap(_device, _driver, _sceneManager);
		initGame(gameData);
	} else {
		gameData = _client->getInfosInGame();
	}
	firstTurn = false;
	if (_device->isWindowActive())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
		manageBomb(gameData);
		displayPlayers();
		changePlayerPostion(gameData);
		manageBonus(gameData);
		auto player = std::find_if(_players.begin(), _players.end(), [&](struct Players const &playerTest) {
		return playerTest.id == _client->getID();});
		bool isWalking = _servEvent.changeEvent(*_event, _client);
		_client->handleEvents(*_event);
	        _sceneManager->drawAll();
		_driver->endScene();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
	std::vector<int> dels;
	int i = 0;
	for (auto &elem : _sounds) {
		if (elem->getStatus() == sf::Sound::Status::Stopped)
			dels.push_back(i);
		i++;
	}
	while (dels.size()) {
		_sounds.erase(_sounds.begin() + dels[dels.size() - 1]);
		dels.pop_back();
	}
}

void InGame::desactivate()
{
	_isActivate = false;
	_sounds.clear();
}