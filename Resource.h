#pragma once
#include "Ship.h"

class Resource : public GameObject {
protected:
    bool collected;

public:
    Resource(
        sf::Vector2f size,
        sf::Vector2f pos,
        sf::Color color
    ) : GameObject(size, pos, color), collected(false) {}

    void update(float) override {}

    void draw(sf::RenderWindow& window) override {
        if (!collected) {
            drawResource(window);
        }
    }

    bool isCollected() const {
        return collected;
    }

    virtual void applyTo(Ship& ship) = 0;

    virtual void drawResource(sf::RenderWindow& window) {
        GameObject::draw(window);
    }

    void collect(Ship& ship) {
        if (collected) return;

        applyTo(ship);
        collected = true;
    }
};


// =====================================
// FUEL BARREL
// =====================================

class Fuel : public Resource {
public:
    Fuel(sf::Vector2f pos)
        : Resource(
            sf::Vector2f(24, 24),
            pos,
            sf::Color::Yellow
        ) {}

    void applyTo(Ship& ship) override {
        ship.addFuel(30.f);
    }

    void drawResource(sf::RenderWindow& window) override {

        sf::Vector2f p = shape.getPosition();

        // Barrel body
        sf::RectangleShape barrel(
            sf::Vector2f(22, 24)
        );

        barrel.setPosition(p);
        barrel.setFillColor(sf::Color(190, 115, 45));
        barrel.setOutlineThickness(1.5f);
        barrel.setOutlineColor(sf::Color(95, 55, 25));

        window.draw(barrel);

        // Barrel bands
        for (int i = 0; i < 3; i++) {

            sf::RectangleShape band(
                sf::Vector2f(22, 3)
            );

            band.setPosition(
                p.x,
                p.y + 5 + i * 8
            );

            band.setFillColor(
                sf::Color(75, 80, 85)
            );

            window.draw(band);
        }

        // Highlight
        sf::RectangleShape shine(
            sf::Vector2f(3, 14)
        );

        shine.setPosition(
            p.x + 4,
            p.y + 5
        );

        shine.setFillColor(
            sf::Color(240, 185, 100)
        );

        window.draw(shine);
    }
};


// =====================================
// TREASURE CHEST
// =====================================

class Treasure : public Resource {
public:
    Treasure(sf::Vector2f pos)
        : Resource(
            sf::Vector2f(24, 24),
            pos,
            sf::Color(255, 215, 0)
        ) {}

    void applyTo(Ship& ship) override {
        ship.addScore(50);
    }

    void drawResource(sf::RenderWindow& window) override {

        sf::Vector2f p = shape.getPosition();

        // Chest body
        sf::RectangleShape chest(
            sf::Vector2f(24, 15)
        );

        chest.setPosition(
            p.x,
            p.y + 9
        );

        chest.setFillColor(
            sf::Color(135, 75, 35)
        );

        chest.setOutlineThickness(1.5f);

        chest.setOutlineColor(
            sf::Color(75, 40, 20)
        );

        window.draw(chest);


        // Golden lid
        sf::RectangleShape lid(
            sf::Vector2f(24, 7)
        );

        lid.setPosition(
            p.x,
            p.y + 4
        );

        lid.setFillColor(
            sf::Color(225, 165, 40)
        );

        lid.setOutlineThickness(1.f);

        lid.setOutlineColor(
            sf::Color(120, 75, 20)
        );

        window.draw(lid);


        // Lock
        sf::RectangleShape lock(
            sf::Vector2f(5, 7)
        );

        lock.setPosition(
            p.x + 10,
            p.y + 12
        );

        lock.setFillColor(
            sf::Color(255, 220, 75)
        );

        window.draw(lock);
    }
};