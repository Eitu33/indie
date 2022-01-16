/*
** EPITECH PROJECT, 2019
** oop_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include <algorithm>
#include <cmath>
#include <boost/lexical_cast.hpp>
#include <iostream>
#if _WIN64
#include <windows.h>

LARGE_INTEGER
getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return (t);
}

int clock_gettime(int X, timestruct *tv)
{
    LARGE_INTEGER t;
    FILETIME f;
    double microseconds;
    static LARGE_INTEGER offset;
    static double frequencyToMicroseconds;
    static int initialized = 0;
    static BOOL usePerformanceCounter = 0;

    if (!initialized)
    {
        LARGE_INTEGER performanceFrequency;
        initialized = 1;
        usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
        if (usePerformanceCounter)
        {
            QueryPerformanceCounter(&offset);
            frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
        }
        else
        {
            offset = getFILETIMEoffset();
            frequencyToMicroseconds = 10.;
        }
    }
    if (usePerformanceCounter)
        QueryPerformanceCounter(&t);
    else
    {
        GetSystemTimeAsFileTime(&f);
        t.QuadPart = f.dwHighDateTime;
        t.QuadPart <<= 32;
        t.QuadPart |= f.dwLowDateTime;
    }

    t.QuadPart -= offset.QuadPart;
    microseconds = (double)t.QuadPart / frequencyToMicroseconds;
    t.QuadPart = microseconds;
    tv->tv_sec = t.QuadPart / 1000000;
    tv->tv_nsec = t.QuadPart % 1000000;
    return (0);
}
#endif

static const int TILESIZE = 50;
static const int HITBOX = 50;
static const int PHIT = 30;
static const int BEXP_TIMER = 1;
static const int BHOLD_TIMER = 3;


game_logic::Bomb::Bomb(unsigned int playerId, float x, float y, unsigned int power, float expSpeed)
    : _playerId(playerId),
      _position(std::pair<float, float>(x, y)),
      _power(power),
      _state(BombState::DROPPED),
      _expSize(std::vector<int>{-1, -1, -1, -1}),
      _expSpeed(0)
{
#if __linux__
    clockid_t clk_id;
    clk_id = CLOCK_MONOTONIC;

    clock_gettime(clk_id, &_startTimer);
#endif
#if _WIN64
    clock_gettime(0, &_startTimer);
#endif
}

game_logic::Bomb::Bomb(float x, float y, unsigned int power, const BombState &state)
    : _position(std::pair<float, float>(x, y)),
      _power(power),
      _state(state),
      _expSize(std::vector<int>{-1, -1, -1, -1}),
      _expSpeed(0)
{
#if __linux__
    clockid_t clk_id;
    clk_id = CLOCK_MONOTONIC;

    clock_gettime(clk_id, &_startTimer);
#endif
#if _WIN64
    clock_gettime(0, &_startTimer);
#endif
}

void game_logic::Bomb::update()
{
    if (_state == BombState::OVER)
        return;
#if __linux__
    clockid_t clk_id;
    struct timespec sp;
    clk_id = CLOCK_MONOTONIC;

    clock_gettime(clk_id, &sp);
#endif
#if _WIN64
    timestruct sp;
    clock_gettime(0, &sp);
#endif
    if (_state == BombState::DETONATED && (sp.tv_sec - _expTimer.tv_sec) >= BEXP_TIMER - _expSpeed)
    {
        _state = BombState::OVER;
    }
    else if (_state == BombState::DROPPED && (sp.tv_sec - _startTimer.tv_sec) >= BHOLD_TIMER - _expSpeed)
    {
        detonate();
    }
}

void game_logic::Bomb::detonate()
{
    _state = BombState::DETONATED;
#if __linux__
    clockid_t clk_id;
    clk_id = CLOCK_MONOTONIC;

    clock_gettime(clk_id, &_expTimer);
#endif
#if _WIN64
    clock_gettime(0, &_expTimer);
#endif
}

bool game_logic::Bomb::playerHit(std::pair<float, float> ppos)
{
    if (_state != BombState::DETONATED)
        return false;

    for (std::size_t i = 0; i <= _expSize[Direction::UP]; i++)
        if (_playerCollider(ppos, 0.f, -(float)i * TILESIZE))
            return true;
    for (std::size_t i = 1; i <= _expSize[Direction::DOWN]; i++)
        if (_playerCollider(ppos, 0.f, (float)i * TILESIZE))
            return true;
    for (std::size_t i = 1; i <= _expSize[Direction::LEFT]; i++)
        if (_playerCollider(ppos, -(float)i * TILESIZE, 0.f))
            return true;
    for (std::size_t i = 1; i <= _expSize[Direction::RIGHT]; i++)
        if (_playerCollider(ppos, (float)i * TILESIZE, 0.f))
            return true;
    return false;
}

bool game_logic::Bomb::_playerCollider(std::pair<float, float> ppos, float x, float y)
{
    if (ppos.first > _position.first + x - PHIT && ppos.first < _position.first + x + HITBOX && ppos.second > _position.second + y - PHIT && ppos.second < _position.second + y + HITBOX)
        return true;
    return false;
}

void game_logic::Bomb::wallsCollider(std::vector<Wall> &walls)
{
    if (_state != BombState::DETONATED)
        return;
    for (std::size_t i = 1; i <= _power; i++)
    {
        _wallCollider(walls, Direction::UP, 0.f, -(float)i * TILESIZE);
        _wallCollider(walls, Direction::DOWN, 0.f, (float)i * TILESIZE);
        _wallCollider(walls, Direction::LEFT, -(float)i * TILESIZE, 0.f);
        _wallCollider(walls, Direction::RIGHT, (float)i * TILESIZE, 0.f);
    }
    for (std::size_t i = 0; i < 4; i++)
    {
        if (_expSize[i] == -1)
            _expSize[i] = _power;
    }
}

void game_logic::Bomb::_wallCollider(std::vector<Wall> &walls, Direction direction, float x, float y)
{
    if (_expSize[direction] != -1)
        return;
    auto it = find_if(walls.begin(), walls.end(), [&](Wall const &wall) {
        return wall.getPosition() == std::pair<float, float>(_position.first + x, _position.second + y);
    });
    if (it != walls.end())
    {
        _expSize[direction] = std::abs((x != 0.f) ? x / TILESIZE : y / TILESIZE);
        if (it->isTough())
        {
            _expSize[direction] -= 1;
        }
        else if (!it->bonusMode())
        {
            it->destroy();
        }
    }
}

void game_logic::Bomb::bombsCollider(std::vector<Bomb> &bombs)
{
    if (_state != BombState::DETONATED)
        return;
    for (std::size_t i = 1; i <= _expSize[Direction::UP]; i++)
        _bombCollider(bombs, 0.f, -(float)i * TILESIZE);
    for (std::size_t i = 1; i <= _expSize[Direction::DOWN]; i++)
        _bombCollider(bombs, 0.f, (float)i * TILESIZE);
    for (std::size_t i = 1; i <= _expSize[Direction::LEFT]; i++)
        _bombCollider(bombs, -(float)i * TILESIZE, 0.f);
    for (std::size_t i = 1; i <= _expSize[Direction::RIGHT]; i++)
        _bombCollider(bombs, (float)i * TILESIZE, 0.f);
}

void game_logic::Bomb::_bombCollider(std::vector<Bomb> &bombs, float x, float y)
{
    auto it = find_if(bombs.begin(), bombs.end(), [&](Bomb const &bomb) {
        return bomb._position == std::pair<float, float>(_position.first + x, _position.second + y);
    });
    if (it != bombs.end() && it->getState() == BombState::DROPPED)
    {
        it->detonate();
    }
}

void game_logic::Bomb::serialize(std::string &sdata) const
{
    if (_state == BombState::OVER)
        return;
    sdata += boost::lexical_cast<std::string>(_position.first) + ",";
    sdata += boost::lexical_cast<std::string>(_position.second) + ",";
    for (std::size_t i = 0; i < 4; i++)
        sdata += boost::lexical_cast<std::string>(_expSize[i]) + ",";
    sdata += ";";
}

game_logic::Bomb::BombState game_logic::Bomb::getState() const
{
    return _state;
}

std::pair<float, float> game_logic::Bomb::getPosition() const
{
    if (_state == BombState::OVER) {
        return (std::pair<float, float>(-1000, -1000));
    } else
        return _position;
}

bool game_logic::Bomb::isOwner(unsigned int id) const
{
    return (id == _playerId) ? true : false;
}
