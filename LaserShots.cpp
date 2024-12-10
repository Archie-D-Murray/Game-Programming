#pragma once

#include "LaserShots.h"
#include "LaserComponents.h"

static constexpr float toRad = 3.14159265f / 180;
void makeLaser(sf::Vector2f position, float speed, float rotation, std::vector<Laser*>& lasers) {
    lasers.push_back(new Laser(position));
    lasers.back()->addComponent(dynamic_cast<LaserComponent*>(new LaserInitialisation(speed, rotation)));
    lasers.back()->addComponent(dynamic_cast<LaserComponent*>(new LaserMovement()));
}

void Normal::shoot(sf::Vector2f position, float rotation, float speed, std::vector<Laser*>& lasers) {
    makeLaser(position, speed, rotation, lasers);
};

void FourForward::shoot(sf::Vector2f position, float rotation, float speed, std::vector<Laser*>& lasers) {
    float angle = -15.0f;
    for (int i = 0; i < 4; i++) {
        makeLaser(position, speed * 2, rotation + angle, lasers);
        angle += 10.0f;
    }
};

void TwoForwardBackward::shoot(sf::Vector2f position, float rotation, float speed, std::vector<Laser*>& lasers) {
    float angle = -5.0f;
    for (int i = 0; i < 2; i++) {
        makeLaser(position, speed * 2, rotation + angle, lasers);
        angle += 10.0f;
    }
    
    angle = 175.0f;
    for (int i = 0; i < 2; i++) {
        makeLaser(position, speed * 2, rotation + angle, lasers);
        angle += 10.0f;
    }
};

void OneAllDirections::shoot(sf::Vector2f position, float rotation, float speed, std::vector<Laser*>& lasers) {
    int num = 4;
    float angle = 360 / num;
    for (int i = 0; i < num; i++) {
        makeLaser(position, speed * 2, rotation + angle * i, lasers);
    }
};