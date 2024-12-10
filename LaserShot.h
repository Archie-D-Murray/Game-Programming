#pragma once
#include "SFML/Graphics.hpp"
class Laser;

class LaserShot {
public:
    virtual void shoot(sf::Vector2f position, float angle, float speed, std::vector<Laser*>& lasers) {};
};