/*----------------------------------------------------Assessment Task-------------------------------------------------------------
    Refactor the code so that WindowManager.h contains the class definition and WindowManager.cpp contains the implementation.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <memory>
#include <iostream>

class WindowManager {
private:
    float textSize;
    int score, level, powerUp;
    enum STATE { PLAYING, GAMEOVER };
    STATE gameState;

    std::unique_ptr<sf::RenderWindow> window;

    sf::Font font;
    sf::Text scoreText, levelText, gameOverText;
    sf::RectangleShape hudBar;
    sf::Sprite powerUpSprite;
    sf::Texture powerUpTextures[4];

    WindowManager();
    void loadPowerUpTextures();

public:
    void drawUI(); //draw all UI components on 

    void updateScore(int value); //Set score text to the current 

    void updateLevel(int value); //Set level text to the current 

    void updatePowerUp(int value); //Set the powerUpSprite to the current powerUp

    void setGameOverText();

    static WindowManager& getInstance();

    sf::RenderWindow& getWindow() const;

    const sf::Vector2u& getSize() const;

    void setGameOver();
};
