#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Laser.h"
#include "Player.h"
#include "Utils.h"

class FastEnemy {
    Utils utils;

    sf::Vector2f position;
    sf::Texture texture;
    sf::Clock delay;
    sf::Sprite enemy;

    static constexpr float speed = 150.f;
    float spawnDelay;
    bool enabled;

public:
    FastEnemy(sf::Vector2f position, float spawnDelay = 0) : position(position), spawnDelay(spawnDelay), enabled(false) {
        if (!texture.loadFromFile("./assets/enemy_type_two.png")) {
            std::cout << "Cannot load Enemy sprite\n";
        }
        enemy.setTexture(texture);
        enemy.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        enemy.setPosition(position);
    }

    ~FastEnemy() {}

    void draw(sf::RenderWindow& window) { if (enabled) window.draw(enemy); }

    void onHit() { enemy.setPosition(utils.getOffScreenSpawnPosition()); }

    const sf::Vector2f& getPosition() const { return enemy.getPosition(); }

    float getRadius() const { return texture.getSize().x / 2; }

    const sf::Vector2u& getSize() const { return texture.getSize(); }

    const sf::FloatRect& getBounds() const { return enemy.getGlobalBounds(); }

    void move(sf::Vector2f vec) { enemy.move(vec); }

    sf::Vector2f vectorToPos(sf::Vector2f position, float dt) const {
        sf::Vector2f dir = position - enemy.getPosition();
        float mag = sqrt(dir.x * dir.x + dir.y * dir.y);
        dir.x = dir.x / mag;
        dir.y = dir.y / mag;
        return dir * dt * speed;
    }

    void update(Player& player, float dt) {
        if (enabled) {
            enemy.move(vectorToPos(player.getPosition(), dt));
            enemy.rotate(speed / 3 * dt);
        } else {
            if (delay.getElapsedTime().asSeconds() >= spawnDelay) {
                enabled = true;
            }
        }
    }
};

