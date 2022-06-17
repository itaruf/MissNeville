#pragma once

#ifndef UTILITIES_H_
#define UTILITIES_H_

#define TRIGGER_OFFSET (24)
#define WALL_OFFSET (128)
#define NEW_PLAYER_POS_OFFSET (32)
#define MIDDLE_WIDTH (APP_VIRTUAL_WIDTH / 2)
#define MIDDLE_HEIGHT (APP_VIRTUAL_HEIGHT / 2)
#define VOLUME (-1500)

#include <string>

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
static std::string GetChar(const T& var)
{
	return std::to_string(var);
}

static std::string Process(std::string const& s, const char letter, bool inclusive = true)
{
    std::string::size_type pos = s.find(letter);
    if (pos != std::string::npos)
        if (inclusive)
            return s.substr(0, pos + 1);
        else
            return s.substr(0, pos);
    else
        return s;
}

static std::string Process2(std::string const& s, const char letter, bool inclusive = true)
{
    std::string::size_type pos = s.find(letter);
    if (pos != std::string::npos)
        if (inclusive)
            return s.substr(pos , s.length() - 1);
        else
            return s.substr(pos + 1, s.length() - 1);
    else
        return s;
}

struct Color
{
    float r = 0;
    float g = 0;
    float b = 0;
};


#endif