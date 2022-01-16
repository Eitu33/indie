/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <irrlicht.h>
#include "driverChoice.h"

class Event : public irr::IEventReceiver {
	public:
		Event();
		~Event() = default;
        	virtual bool OnEvent(const irr::SEvent& event);
       		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

	protected:
	private:
        	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif /* !EVENT_HPP_ */
