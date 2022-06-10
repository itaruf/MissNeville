#pragma once

#ifndef UTILITIES_H_
#define UTILITIES_H_

#define TRIGGER_OFFSET (24)
#define WALL_OFFSET (128)
#define NEW_PLAYER_POS_OFFSET (32)

#include <string>

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
static std::string GetChar(const T& var)
{
	return std::to_string(var);
}

static std::string Process(std::string const& s, const char letter)
{
    std::string::size_type pos = s.find(letter);
    if (pos != std::string::npos)
        return s.substr(0, pos + 1);
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