/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** EventHandleServ
*/

#ifndef EVENTHANDLESERV_HPP_
#define EVENTHANDLESERV_HPP_

#include <string>
#include <irrlicht.h>
#include "EventKeyEnum.hpp"
#include "Event.hpp"
#include "Client.hpp"
#include "InGame.hpp"

class EventHandleServ {
	public:
		EventHandleServ() = default;
		~EventHandleServ() = default;

		bool changeEvent(const Event &keyCode, const std::shared_ptr<IClient> &client)
		{
			std::string event;
			
			if (keyCode.IsKeyDown(irr::KEY_RIGHT)) {
				client->sendEvent(std::to_string(static_cast<int>(EventType::MoveRight)));
				return (true);
			}
			if (keyCode.IsKeyDown(irr::KEY_LEFT)) {
				client->sendEvent(std::to_string(static_cast<int>(EventType::MoveLeft)));
				return (true);
			}
			if (keyCode.IsKeyDown(irr::KEY_UP)) {
				client->sendEvent(std::to_string(static_cast<int>(EventType::MoveUp)));
				return (true);
			}
			if (keyCode.IsKeyDown(irr::KEY_DOWN)) {
				client->sendEvent(std::to_string(static_cast<int>(EventType::MoveDown)));
				return (true);
			}
			if (keyCode.IsKeyDown(irr::KEY_SPACE)) {
				client->sendEvent(std::to_string(static_cast<int>(EventType::PutBomb)));
			}
			return (false);
		};

	protected:
	private:

};

#endif /* !EVENTHANDLESERV_HPP_ */