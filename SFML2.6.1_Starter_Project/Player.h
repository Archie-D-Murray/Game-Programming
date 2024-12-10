#pragma once
#include <cstdlib>
#include <iostream>
#include "Laser.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "WindowManager.h"
#include "LaserComponents.h"
#include "LaserShots.h"

class Player {
private:
    sf::Sprite player;
    sf::Texture texture;
    sf::Clock  powerUpLifeTimer;
    LaserShot* shotType;
    std::vector<Laser*> lasers;

    static constexpr float toRad = 3.14159265f / 180;
    float powerUpLifeTime;
    float roundShotTimer = 0.0f;
    float speed;
    bool fired;

    enum SHOT { ONEFORWARD = 0, FOURFORWARD, TWOFORWADBACKWARD, ONEALLDIRECTIONS };
    SHOT laserShot;

public:
    Player() : speed(300.0f), fired(false), laserShot(ONEFORWARD), powerUpLifeTime(12000) {
        shotType = new Normal();
        if (!texture.loadFromFile("./assets/player.png")) {
            std::cout << "Cannot load Player sprite\n";
        }
        player.setTexture(texture);
        player.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        player.setPosition(WindowManager::getInstance().getSize().x / 2, WindowManager::getInstance().getSize().y / 2);
    }

    std::vector<Laser*>& getLasers() {
        return lasers;
    }

    const sf::Vector2f& getPosition() const {
        return player.getPosition();
    }

    float getRotation() const {
        return player.getRotation();
    }

    const sf::FloatRect& getBounds() const {
        return player.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < lasers.size(); i++) {

            if (lasers[i] != nullptr) {
                lasers[i]->draw(window);
            }
        }
        window.draw(player);
    };

    void makeLaser(sf::Vector2f position, float speed, float rotation) {
        lasers.push_back(new Laser(position));
        lasers.back()->addComponent(dynamic_cast<LaserComponent*>(new LaserInitialisation(speed, rotation)));
        lasers.back()->addComponent(dynamic_cast<LaserComponent*>(new LaserMovement()));
    }

    void update(float dt) {
        sf::Vector2f movement(0.0f, 0.0f);

        //Check AD keydown and rotate the player accordingly
        if (InputManager::Instance().KeyDown(sf::Keyboard::Key::A)) {
            player.rotate(-speed * dt);
        } else if (InputManager::Instance().KeyDown(sf::Keyboard::Key::D)) {
            player.rotate(speed * dt);
        }

        /*----------------------------------------------------Assessment Task-------------------------------------------------------------
            Refactor this shooting code to use a state pattern rather than if else statements
        */
        if (InputManager::Instance().KeyPressed(sf::Keyboard::Key::Space)) {
            shotType->shoot(getPosition(), getRotation(), speed, lasers);
        }
        
        // TASK: A.VI
        /*----------------------------------------------------Assessment Task-------------------------------------------------------------
        Implement round shot here
        The shot should be fired when LShift key is pressed
        It should have a cooldown time of 20s
        */
        const float shotAngle = 360.0f / 36.0f;
        if (InputManager::Instance().KeyPressed(sf::Keyboard::LShift) && roundShotTimer == 0.0f) {
            for (float angle = 0; angle < 360.0f; angle += shotAngle) {
                makeLaser(player.getPosition(), speed, angle);
            }
            roundShotTimer = 20.0f;
        }
        roundShotTimer = max(0.0f, roundShotTimer - dt);

        if (laserShot != ONEFORWARD && powerUpLifeTimer.getElapsedTime().asMilliseconds() > powerUpLifeTime) {
            setLaserShotType(0);
        }

        for (auto it = lasers.begin(); it != lasers.end(); ) {
            if ((*it)->shouldBeDestroyed()) {
                delete* it;
                *it = nullptr;
            }

            if (*it == nullptr) {
                it = lasers.erase(it);
            } else {
                (*it)->update(dt);
                ++it;
            }
        }
    }

    void setLaserShotType(int shot) {
        constexpr SHOT types[] = { ONEFORWARD, FOURFORWARD, TWOFORWADBACKWARD, ONEALLDIRECTIONS };
        switch (types[shot]) {
        case FOURFORWARD:
            shotType = new FourForward();
            break;
        case TWOFORWADBACKWARD:
            shotType = new TwoForwardBackward();
            break;
        case ONEALLDIRECTIONS:
            shotType = new OneAllDirections();
            break;
        default:
            shotType = new Normal();
        }
        laserShot = types[shot];
        WindowManager::getInstance().updatePowerUp(shot);
        powerUpLifeTimer.restart();
    }

    float getRadius() const {
        return texture.getSize().x;
    }
};


