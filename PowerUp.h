#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "WindowManager.h"
#include "Utils.h"

class PowerUp {
protected:
    Utils utils;

    sf::Texture texture;
    sf::Sprite powerUp;
    sf::Clock lifeTimer;

    static constexpr float lifeTime = 10000;
    bool destroy;
    string type;
    string filePath;

public:
    PowerUp() : filePath("assets/power_up_type_one.png"), destroy(false) {
        utils.loadTexture(texture, filePath);
        powerUp.setTexture(texture);
        powerUp.setPosition(utils.getOnScreenSpawnPosition());
        powerUp.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        powerUp.setScale(2, 2);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(powerUp);
    }

    void update() {
        if (!destroy && lifeTimer.getElapsedTime().asMilliseconds() >= lifeTime) {
            destroy = true;
        }
    }

    const sf::Vector2f& getPosition() const {
        return powerUp.getPosition();
    }

    float getRadius() const {
        return powerUp.getGlobalBounds().getSize().x / 2;
    }

    bool shoudBeDestroyed() const {
        return destroy;
    }

    void onHit() {
        destroy = true;
    }
};