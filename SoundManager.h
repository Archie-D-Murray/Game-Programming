/*----------------------------------------------------Assessment Task-------------------------------------------------------------
    Create a singleton class called SoundManager for loading and playing sounds in the game.
    To test that it works, use it to play the hit.ogg sound whenever an enemy is hit.
*/
#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
    ~SoundManager();
    SoundManager();
    static SoundManager* instance;
public:
    sf::Sound playerHitSound;
    sf::SoundBuffer hitBuffer;
    static SoundManager& GetInstance();
    static void Start();
    static void Stop();
};