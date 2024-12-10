#pragma once
#include "Player.h"
#include "SlowEnemy.h"
#include "FastEnemy.h"
#include <ctime>
#include "WindowManager.h"
#include "PowerUp.h"
#include "Utils.h"
#include "ExplodedParticles.h"

class GameManager {
    /*----------------------------------------------------Assessment Task-------------------------------------------------------------
        All the fields and methods of the GameManager class are currently public, however, not all members of the class need to be public.
        Update the class to apply the right access controls.
    */
    // TASK: A.III
    std::vector<unique_ptr<ExplodedParticles>> enemyBits;
    Player* player;
    Utils utils;
    std::vector<SlowEnemy*> slowEnemies;
    std::vector<FastEnemy*> fastEnemies;
    std::vector<Laser*>& lasers;
    std::vector<PowerUp*> powerUps;
    enum STATE { PLAYING, GAMEOVER };
    STATE gameState;
    sf::Vector2u windowSize;
    sf::Clock powerUpTimer;
    bool spawnPowerUp;
    float powerUpDelay;
    int score;
    int level;
public:

    GameManager();

    void draw(sf::RenderWindow& window) const;

    void update(float dt);

    void nextLevel();

    void createSlowEnemies(int num, int delay);

    void createFastEnemies(int num, int delay);

    void increaseScore();

    void resolveLaserCollisionsWithPowerUps(std::vector<Laser*>& lasers, std::vector<PowerUp*>& powerUps, Player& player);

    void resolveFastEnemyCollisionsWithPlayer(const Player& player, const std::vector<FastEnemy*>& enemies);

    void resolveSlowEnemyCollisionsWithPlayer(const Player& player, const std::vector<SlowEnemy*>& enemies);

    template <typename EnemyType> void resolveEnemyCollisionsWithPlayer(const Player& player, const std::vector<EnemyType*>& enemies);

    template <typename T1, typename T2>
    bool checkCollisionBetweenTwoObjects(T1& object1, T2& object2) const {
        sf::Vector2f pos1 = object1.getPosition();
        sf::Vector2f pos2 = object2.getPosition();

        float distance = std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
        float combinedRadii = object1.getRadius() + object2.getRadius();
        return distance <= combinedRadii;
    }

    template <typename T1, typename T2>
    void resolveEnemyCollisionsWithLasers(std::vector<T1*>& lasers, std::vector<T2*>& others) {
        for (int i = 0; i < lasers.size(); i++) {
            if (lasers[i] != nullptr) {
                for (int j = 0; j < others.size(); j++) {
                    // TASK: A.VII
                    if (checkCollisionBetweenTwoObjects(*lasers[i], *others[j])) {
                        increaseScore();
                        enemyBits.push_back(make_unique<ExplodedParticles>(others[j]->getPosition()));
                        others[j]->onHit();
                        utils.deleteFromContainer(lasers[i], lasers, i);
                        i++;
                        break;
                    }
                }
            }
        }
    }
};
