/*----------------------------------------------------Assessment Task-------------------------------------------------------------
    Create a new enemy class that is the same as the SlowEnemy except for two differences,
    it should use the enemy_type_three.png sprite and its rotate() method should rotate it at the same speed as its movement speed.
    Using Polymorphism, add pointers to two new instances of the new enemy class to the slowEnemies vector in GameManger.h when the player reaches level 3.
*/

#pragma once
// TASK: B.III
#include "SlowEnemy.h"
#include <SFML/Graphics.hpp>
class NewEnemy : public SlowEnemy { 
public:
    NewEnemy(sf::Vector2f position, float spawnDelay = 0);
    void rotate(float dt);
};
