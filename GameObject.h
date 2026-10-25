#pragma once
#include <SFML/Graphics.hpp>

// Abstract base class: every object in the game is a GameObject.
class GameObject {
protected:
    sf::RectangleShape shape;   // what we draw and use for collision

public:
    GameObject(sf::Vector2f size, sf::Vector2f pos, sf::Color color) {
        shape.setSize(size);
        shape.setPosition(pos);
        shape.setFillColor(color);
    }
    virtual ~GameObject() {}

    virtual void update(float dt) = 0;   // pure virtual -> class is abstract
    virtual void draw(sf::RenderWindow& window) { window.draw(shape); }

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};
