#include "NewEnemy.h"

NewEnemy::NewEnemy(sf::Vector2f position, float spawnDelay) : SlowEnemy(position, spawnDelay) {
    if (!texture.loadFromFile("./assets/enemy_type_three.png")) {
        std::cout << "Could not load texture!\n";
    }
    enemy.setTexture(texture);
};

void NewEnemy::rotate(float dt) {
    enemy.rotate(speed * dt);
};
