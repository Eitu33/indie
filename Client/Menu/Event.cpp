/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Event
*/

#include "Event.hpp"

Event::Event()
{
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;
}

bool Event::OnEvent(const irr::SEvent& event)
{
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
}

bool Event::IsKeyDown(irr::EKEY_CODE keyCode) const
{
        return KeyIsDown[keyCode];
}