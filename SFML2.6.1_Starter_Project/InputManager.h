#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class InputManager {
    // use a double buffer for current and last key and mouse button values
    vector<bool> keyBuffers[2];
    vector<bool> mouseBuffers[2];
    int curBuffer = 0;
    InputManager() {
        keyBuffers[0] = vector<bool>(sf::Keyboard::KeyCount, false);
        keyBuffers[1] = vector<bool>(sf::Keyboard::KeyCount, false);
        mouseBuffers[0] = vector<bool>(sf::Mouse::ButtonCount, false);
        mouseBuffers[1] = vector<bool>(sf::Mouse::ButtonCount, false);
    }

public:
    static InputManager& Instance() {
        static InputManager instance;
        return instance;
    }

    void Update() {
        for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
            keyBuffers[curBuffer ^ 1][i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
        }
        for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
            mouseBuffers[curBuffer ^ 1][i] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i));
        }
        curBuffer ^= 1;
    }

    bool KeyDown(sf::Keyboard::Key k) const { return keyBuffers[curBuffer][k]; }
    bool KeyPressed(sf::Keyboard::Key k) const { return !keyBuffers[curBuffer][k] && keyBuffers[curBuffer ^ 1][k]; }
    bool ButtonDown(sf::Mouse::Button b) const { return mouseBuffers[curBuffer][b]; }
    bool ButtonPressed(sf::Mouse::Button b) const { return !mouseBuffers[curBuffer][b] && mouseBuffers[curBuffer ^ 1][b]; }
};