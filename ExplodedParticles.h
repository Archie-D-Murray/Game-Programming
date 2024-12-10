#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>
#include "Utils.h"
#include "SoundManager.h"

class ExplodedParticles {
private:

    Utils util;
    struct Particle {
        sf::CircleShape triangle;
        sf::Vector2f velocity;
        float lifeTime;
        int memoryLeakTest[99999];
    };

    std::vector<Particle*> particles;
    sf::Vector2f position;
    static constexpr float lifeTime = 2000;
    static constexpr float speed = 50;
    static constexpr int numParticles = 50;
    sf::Color color;
    sf::Clock clock;

public:
    /*----------------------------------------------------Assessment Task-------------------------------------------------------------
        Refactor the ExplodedParticles class constructor to accept a hit enemy's position as a parameter and then use it to position instances.
        Pass the position from the resolveEnemyCollisionsWithLasers method in GameManager.h where ExplodedParticles instances are created
    */
    ExplodedParticles(const sf::Vector2f& position = {300, 300}) {
        SoundManager::GetInstance().playerHitSound.play();
        this->position = position;
        color = sf::Color::Black;
        for (int i = 0; i < numParticles; ++i) {
            Particle* particle = new Particle();
            particle->triangle = sf::CircleShape(10, 3);
            particle->triangle.setPosition(position.x + util.randomInt(-50, 50), position.y + util.randomInt(-50, 50));
            particle->lifeTime = util.randomFloat(0, lifeTime / 2);
            particle->triangle.setFillColor(sf::Color::Black);
            particle->velocity = util.randomDirection() * util.randomFloat(5, speed);
            particles.push_back(particle);
        }

    }
    ~ExplodedParticles() {}

    void update(float dt) {
        float elapsed = clock.getElapsedTime().asMilliseconds();

        /*----------------------------------------------------Assessment Task-------------------------------------------------------------
            Make sure particle pointers in the particles vector that have lived past their lifetime are properly deleted
        */
        if (elapsed < lifeTime) {
            for (auto it = particles.begin(); it != particles.end();) {
                Particle* particle = *it;
                if (elapsed < particle->lifeTime) { //move particle if it still has lifetime left
                    particle->triangle.move(particle->velocity * dt);
                    ++it;
                } else { //properly delete particle if it has exhausted its lifetime
                    // TASK: A.II
                    delete particle;
                    it = particles.erase(it);
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& particle : particles) {
            window.draw(particle->triangle);
        }
    }

    bool shouldDestroy() const {
        return clock.getElapsedTime().asMilliseconds() >= lifeTime;
    }
};
