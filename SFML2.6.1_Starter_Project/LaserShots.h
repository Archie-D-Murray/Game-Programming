#pragma once

#include "LaserShot.h"
#include "Laser.h"
// FOURFORWARD, TWOFORWADBACKWARD, ONEALLDIRECTIONS
class Normal : public LaserShot {
public:
    Normal() {}
    void shoot(sf::Vector2f position, float angle, float speed, std::vector<Laser*>& lasers) override;
};

class FourForward : public LaserShot {
public:
    FourForward() {}
    void shoot(sf::Vector2f position, float angle, float speed, std::vector<Laser*>& lasers) override;
};

class TwoForwardBackward: public LaserShot {
public:
    TwoForwardBackward() {}
    void shoot(sf::Vector2f position, float angle, float speed, std::vector<Laser*>& lasers) override;
};

class OneAllDirections: public LaserShot {
public:
    OneAllDirections() {}
    void shoot(sf::Vector2f position, float angle, float speed, std::vector<Laser*>& lasers) override;
};