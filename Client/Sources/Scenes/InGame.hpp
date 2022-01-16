/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** InGame
*/

#ifndef INGAME_HPP_
#define INGAME_HPP_

#include "SFML/Audio.hpp"

#include "MapDisplayer.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "EventHandleServ.hpp"

class InGame : public Scene {
	struct Walls
	{
		irr::core::vector3df pos;
		bool isBonus;
		bool isTough;
		irr::scene::IMeshSceneNode* node;
		game_logic::Bonus bonus;
	};
	struct Players
	{
		irr::core::vector3df pos;
		unsigned int id;
		bool isAlive;
		bool isWalking;
		irr::scene::IAnimatedMeshSceneNode *node;
	};

	struct Bombs
	{
		irr::core::vector3df pos;
		bool explosing;
		irr::scene::IAnimatedMeshSceneNode* node;
		std::vector<irr::scene::IMeshSceneNode*> explosion;
	};
	public:
		InGame(	Event *event, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
			irr::scene::ISceneManager *sceneManager, std::shared_ptr<IClient> client);
		~InGame() {};

		void run();

		void activate() {_isActivate = true;};
		void activate(int win) {_isActivate = true;};
		void desactivate();
		void initGame(game_logic::GameData gameData);
		void handleEventChangeScene(std::shared_ptr<Scene> toActivate) {};
		void displayPlayers();
		void changePlayerPostion(game_logic::GameData);
		void manageBomb(game_logic::GameData gameData);
		void removeWall(irr::scene::IMeshSceneNode*node);
		void manageBonus(game_logic::GameData);
	protected:
	private:
		MapDisplayer _mapDisplayer;
		std::vector<irr::core::vector3df> _undestroyable;
		std::vector<struct Walls> _walls;
		std::vector<struct Players> _players;
		std::vector<struct Walls> _bonus;
		std::vector<struct Bombs> _bombs;
		EventHandleServ _servEvent;
		bool _isWalking = false;

		std::vector<std::shared_ptr<sf::Sound>> _sounds;
		std::vector<sf::SoundBuffer> _buffer;
		bool firstTurn = true;
};

#endif /* !INGAME_HPP_ */