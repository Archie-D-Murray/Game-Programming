//Separate the WindowManager.h header file into a header and an implementation file.
//The implementation should be provided in this file.

// TASK: A.I

#include "WindowManager.h"

WindowManager::WindowManager() : score(0), level(0), powerUp(0), gameState(PLAYING) {
    int width = (sf::VideoMode::getDesktopMode()).width / 2;
    int height = width * 0.75;

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Space Shooter Demo");
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);
    textSize = window->getSize().x * 0.04;

    if (!font.loadFromFile("assets/font.ttf")) {
        std::cout << "Cannot load font!\n";
    }
    hudBar = sf::RectangleShape(sf::Vector2f(window->getSize().x, textSize * 1.2));
    hudBar.setFillColor(sf::Color(50, 50, 50));

    updateScore(score);
    updateLevel(level);
    loadPowerUpTextures();
    updatePowerUp(powerUp);
    setGameOverText();
};

void WindowManager::loadPowerUpTextures() {
    for (int i = 0; i < 4; i++) {
        std::stringstream ss;
        ss << "./assets/power_up_" << i << ".png";
        if (!powerUpTextures[i].loadFromFile(ss.str())) {
            std::cout << "Cannot load sprite " << ss.str() << "\n";
        }
    }

    powerUpSprite.setTexture(powerUpTextures[0]);
    powerUpSprite.setPosition(window->getSize().x / 2, textSize * 0.1);
    powerUpSprite.setOrigin(powerUpSprite.getGlobalBounds().getSize().x / 2, 0);
    powerUpSprite.scale(textSize / powerUpTextures[0].getSize().x, textSize / powerUpTextures[0].getSize().x);
};

void WindowManager::drawUI() {
    window->draw(hudBar);
    window->draw(scoreText);
    window->draw(levelText);
    window->draw(powerUpSprite);
    if (gameState == GAMEOVER) { window->draw(gameOverText); }
};

void WindowManager::updateScore(int value) {
    score = value;
    std::stringstream scoreStream;
    scoreStream << "Score: " << score;
    scoreText = sf::Text(scoreStream.str(), font, textSize);
    scoreText.setOrigin(scoreText.getGlobalBounds().getSize().x, 0);
    scoreText.setPosition(window->getSize().x - textSize / 2, 0);
};

void WindowManager::updateLevel(int value) {
    level = value;
    std::stringstream levelStream;
    levelStream << "Level: " << level;
    levelText = sf::Text(levelStream.str(), font, textSize);
    levelText.setPosition(textSize / 2, 0);
};

void WindowManager::updatePowerUp(int value) {
    powerUp = value;
    powerUpSprite.setTexture(powerUpTextures[powerUp]);
};

void WindowManager::setGameOverText() {
    gameOverText = sf::Text("GAME OVER", font, textSize);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(window->getSize().x / 2, window->getSize().y / 2);
};

WindowManager& WindowManager::getInstance() {
    static WindowManager gameWindow;
    return gameWindow;
};

sf::RenderWindow& WindowManager::getWindow() const {
    return *window;
};

const sf::Vector2u& WindowManager::getSize() const {
    return window->getSize();
}

void WindowManager::setGameOver() {
    gameState = GAMEOVER;
};
