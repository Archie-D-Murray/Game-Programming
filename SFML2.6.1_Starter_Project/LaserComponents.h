#include "Laser.h"

//TASK B.II

class LaserInitialisation : public LaserComponent {

    float speed = 0, rotation = 0;

    public:
    LaserInitialisation(float speed, float rotation) : speed(speed), rotation(rotation) {};
    virtual void init() override {
        entity->speed = speed;
        entity->rotation = rotation;
    };
};

class LaserMovement : public LaserComponent {
    static constexpr float toRad = 3.14159265f / 180;

    virtual void update(float dt) override {
        sf::Vector2f movement = {
            entity->speed * std::cos(entity->laser.getRotation() * toRad),
            entity->speed * std::sin(entity->laser.getRotation() * toRad)
        };
        entity->position = entity->position + movement * dt;
        entity->laser.setPosition(entity->position);
        entity->laser.setRotation(entity->rotation);
    };
};
