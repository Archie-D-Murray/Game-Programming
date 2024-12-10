#include "GameManager.h"
#include "NewEnemy.h"

GameManager::GameManager()
    :player(new Player()), gameState(PLAYING), level(0), powerUpDelay(20000), spawnPowerUp(true),
    lasers(player->getLasers()), windowSize(WindowManager::getInstance().getSize()), score(0) {
    nextLevel();
}

/*----------------------------------------------------Assessment Task-------------------------------------------------------------
    The draw method below has 4 index-based for-loops that iterate over 4 vector containers.
    Refactor this code to use 4 iterators instead.
*/
void GameManager::draw(sf::RenderWindow& window) const {
    // for (int i = 0; i < slowEnemies.size(); i++) {
    //     if (slowEnemies[i] != nullptr) {
    //         slowEnemies[i]->draw(window);
    //     }
    // }

    //for (int i = 0; i < enemyBits.size(); i++) {
    //    enemyBits[i]->draw(window);
    //}

    //for (int i = 0; i < fastEnemies.size(); i++) {
    //    if (fastEnemies[i] != nullptr) {
    //        fastEnemies[i]->draw(window);
    //    }
    //}

    //for (int i = 0; i < powerUps.size(); i++) {
    //    if (powerUps[i] != nullptr) {
    //        powerUps[i]->draw(window);
    //    }
    //}
     // IDK if this is right but lgtm
    for (auto it = slowEnemies.begin(); it != slowEnemies.end(); it++) {
        (*it)->draw(window);
    }

    for (auto it = enemyBits.begin(); it != enemyBits.end(); it++) {
        (*it)->draw(window);
    }

    for (auto it = fastEnemies.begin(); it != fastEnemies.end(); it++) {
        (*it)->draw(window);
    }
    for (auto it = powerUps.begin(); it != powerUps.end(); it++) {
        (*it)->draw(window);
    }

    if (gameState == PLAYING) player->draw(window);
}

void GameManager::update(float dt) {
    if (gameState == PLAYING) {
        if (spawnPowerUp && powerUpTimer.getElapsedTime().asMilliseconds() > powerUpDelay) {
            powerUps.push_back(new PowerUp());
            powerUpTimer.restart();
            spawnPowerUp = false;
        }

        for (int i = 0; i < enemyBits.size(); i++) {
            enemyBits[i]->update(dt);
            if (enemyBits[i]->shouldDestroy()) {
                enemyBits.erase(enemyBits.begin() + i);
            }
        }

        for (int i = 0; i < slowEnemies.size(); i++) {
            if (slowEnemies[i] != nullptr) {
                slowEnemies[i]->update(*player, dt);
            }
        }

        for (int i = 0; i < fastEnemies.size(); i++) {
            if (fastEnemies[i] != nullptr) {
                fastEnemies[i]->update(*player, dt);
            }
        }

        for (int i = 0; i < powerUps.size(); i++) {
            if (powerUps[i] != nullptr) {
                if (powerUps[i]->shoudBeDestroyed()) {
                    utils.deleteFromContainer(powerUps[i], powerUps, i);
                    powerUpTimer.restart();
                    spawnPowerUp = true;
                } else powerUps[i]->update();
            }
        }

        if (gameState == PLAYING) player->update(dt);

        resolveEnemyCollisionsWithPlayer(*player, slowEnemies);
        resolveEnemyCollisionsWithPlayer(*player, fastEnemies);
        resolveEnemyCollisionsWithLasers(lasers, slowEnemies);
        resolveEnemyCollisionsWithLasers(lasers, fastEnemies);
        resolveLaserCollisionsWithPowerUps(lasers, powerUps, *player);
    }
}

void GameManager::nextLevel() {
    level++;
    WindowManager::getInstance().updateLevel(level);
    if (level == 1) {
        for (int i = 0; i < 6; i++) {
            createSlowEnemies(1, i * 2);
        }
    } else if (level == 2) {
        for (int i = 0; i < 3; i++) {
            createFastEnemies(1, i * 2);
        }
    // TASK: B.III
    } else if (level == 3) {
        for (int i = 0; i < 4; i++) {
            createSlowEnemies(1, i);
        }
        for (int i = 0; i < 2; i++) {
            slowEnemies.push_back(new NewEnemy(utils.getOffScreenSpawnPosition(), i));
        }
    }
    //Other levels to be specified in the future

}

void GameManager::createSlowEnemies(int num, int delay = 0) {
    for (int i = 0; i < num; i++) {
        slowEnemies.push_back(new SlowEnemy(utils.getOffScreenSpawnPosition(), delay));
    }
}

void GameManager::createFastEnemies(int num, int delay = 0) {
    for (int i = 0; i < num; i++) {
        fastEnemies.push_back(new FastEnemy(utils.getOffScreenSpawnPosition(), delay));
    }
}

void GameManager::increaseScore() {
    score += 10;
    WindowManager::getInstance().updateScore(score);
    if (score > level * 100) {
        nextLevel();
    }
}

void GameManager::resolveLaserCollisionsWithPowerUps(std::vector<Laser*>& lasers, std::vector<PowerUp*>& powerUps, Player& player) {
    for (int i = 0; i < lasers.size(); i++) {
        if (lasers[i] != nullptr) {
            for (int j = 0; j < powerUps.size(); j++) {
                if (checkCollisionBetweenTwoObjects(*lasers[i], *powerUps[j])) {
                    powerUps[j]->onHit();
                    player.setLaserShotType(rand() % 3 + 1);
                    utils.deleteFromContainer(lasers[i], lasers, i);
                    i++;
                    break;
                }
            }
        }
    }
}

/*----------------------------------------------------Assessment Task-------------------------------------------------------------
    The two methods below are very similar. Refactor the code to use a single template function instead.
    Don't forget to update the header file as well
*/
void GameManager::resolveFastEnemyCollisionsWithPlayer(const Player& player, const std::vector<FastEnemy*>& enemies) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (checkCollisionBetweenTwoObjects(player, *enemies[i])) {
            gameState = GAMEOVER;
            WindowManager::getInstance().setGameOver();
            break;
        }
    }
}

void GameManager::resolveSlowEnemyCollisionsWithPlayer(const Player& player, const std::vector<SlowEnemy*>& enemies) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (checkCollisionBetweenTwoObjects(player, *enemies[i])) {
            gameState = GAMEOVER;
            WindowManager::getInstance().setGameOver();
            break;
        }
    }
}

template<typename EnemyType>
void GameManager::resolveEnemyCollisionsWithPlayer(const Player & player, const std::vector<EnemyType*>& enemies) {
    static_assert(std::is_class<SlowEnemy>::value || std::is_class<FastEnemy>::value, "Was not expected type");
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (checkCollisionBetweenTwoObjects(player, *enemies[i])) {
            gameState = GAMEOVER;
            WindowManager::getInstance().setGameOver();
            break;
        }
    }
}
