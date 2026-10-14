#pragma once
#include "GameObject.h"

class Destination : public GameObject {
public:
    Destination()
        : GameObject(sf::Vector2f(60, 140), sf::Vector2f(740, 230), sf::Color(60, 180, 75)) {}
    void update(float) override {}
};
