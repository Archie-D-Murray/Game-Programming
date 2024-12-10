#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include <random>
#include <cmath>

class Utils {
    sf::Vector2u windowSize;

public:
    Utils() :windowSize(WindowManager::getInstance().getSize()) {}

    sf::Vector2f getOffScreenSpawnPosition() {
        int rand = randomInt(0, 4);
        switch (rand) {
        case(0):
            return sf::Vector2f(randomInt(0, windowSize.x), randomInt(-200, -100));
        case(1):
            return sf::Vector2f(randomInt(-200, -100), randomInt(0, windowSize.y));
        case(2):
            return sf::Vector2f(randomInt(-200, -100), randomInt(0, windowSize.y));
        case(3):
            return sf::Vector2f(randomInt(0, windowSize.y), randomInt(-200, -100));
        }
    }

    sf::Vector2f getOnScreenSpawnPosition() {
        int lowerBoundX = 0.1 * windowSize.x;
        int upperBoundX = windowSize.x - lowerBoundX;
        int lowerBoundY = 0.1 * windowSize.y;
        int upperBoundY = windowSize.y - lowerBoundY;

        return sf::Vector2f(randomInt(lowerBoundX, lowerBoundX), randomInt(lowerBoundY, upperBoundY));
    }

    float randomFloat(float min, float max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    float randomInt(int min, int max) {
        return static_cast<int>(randomFloat(min, max));
    }

    sf::Vector2f randomDirection() {
        float angle = randomFloat(0, 360);
        float radian = angle * 3.14159265f / 180.0f;
        return sf::Vector2f(std::cos(radian), std::sin(radian));
    }

    void loadTexture(sf::Texture& texture, const std::string filePath) {
        if (!texture.loadFromFile(filePath)) {
            std::cout << "Cannot load " << filePath << "\n";
        }
    }

    template <typename T1>
    void deleteFromContainer(T1* element, std::vector<T1*>& container, int index) {
        delete element;
        element = nullptr;
        container.erase(container.begin() + index);
    }
};