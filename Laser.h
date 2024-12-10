#pragma once
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "LaserComponent.h"
#include "WindowManager.h"

/*----------------------------------------------------Assessment Task-------------------------------------------------------------
    Refactor the Laser class by extracting its initialization and movement logic into separate components.
    Use the component design pattern to complete this task.
*/

class Laser {
private:
    std::vector<LaserComponent*> components;

public:
    sf::Vector2f position;
    float rotation;
    float speed;
    sf::Texture texture;
    sf::Sprite laser;
    Laser() :Laser(sf::Vector2f(0, 0)) {}

    Laser(sf::Vector2f position) : speed(0), position(position), rotation(0) {
        texture.loadFromFile("./assets/laser.png");
        laser.setTexture(texture);
        laser.setOrigin(16, 16);
        laser.setPosition(position);
    }
    
    ~Laser() {
        for (auto component : components) {
            delete component;
        }
    }

    Laser* addComponent(LaserComponent* component) {
        components.push_back(component);
        components.back()->setParent(this);
        components.back()->init();
        return this;
    }

    void update(float dt) {
        std::vector<int> ints = { 1, 2, 3 };
        for (auto it = components.begin(); it != components.end(); it++) {
            (*it)->update(dt);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(laser);
    }

    sf::FloatRect getBounds() {
        return laser.getGlobalBounds();
    }

    sf::Texture getTexture() {
        return texture;
    }

    sf::Vector2f getPosition() {
        return laser.getPosition();
    }

    float getRadius() {
        return texture.getSize().x / 2;
    }

    bool shouldBeDestroyed() {
        return laser.getPosition().x<0 || laser.getPosition().x> WindowManager::getInstance().getSize().x || laser.getPosition().y<0 || laser.getPosition().y> WindowManager::getInstance().getSize().y;
    }
};

