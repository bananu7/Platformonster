#pragma once
#include <SFML/System/Vector2.hpp>
typedef sf::Vector2f Point;

inline int integralPart(float f) { return static_cast<int>(f); }
enum class Direction {
    Up, Down, Left, Right
};

