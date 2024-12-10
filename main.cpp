#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "WindowManager.h"
#include "SoundManager.h"
int main() {
    // Create the main window
    sf::RenderWindow& window = WindowManager::getInstance().getWindow();

    sf::Clock timer;

    GameManager* game = new GameManager();
    SoundManager::Start();
    float dt = 0;

    while (window.isOpen()) {
        float passed = timer.getElapsedTime().asSeconds();
        dt = passed - dt;

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        game->update(dt);
        dt = passed;

        InputManager::Instance().Update();

        game->draw(window);
        WindowManager::getInstance().drawUI();
        window.display();
    }
    SoundManager::Stop();
    return EXIT_SUCCESS;
}

