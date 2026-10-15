#pragma once
#include "GameObject.h"

class Obstacle : public GameObject {
protected:
    int damage;

public:
    Obstacle(
        sf::Vector2f size,
        sf::Vector2f pos,
        sf::Color color,
        int dmg
    ) : GameObject(size, pos, color), damage(dmg) {}

    void update(float) override {}

    int getDamage() const {
        return damage;
    }
};


// =====================================
// ROCK
// =====================================

class Rock : public Obstacle {
public:
    Rock(sf::Vector2f pos, int damage = 20)
    : Obstacle(
        sf::Vector2f(50, 50),
        pos,
        sf::Color(110, 110, 110),
        damage
    ) {}
    void draw(sf::RenderWindow& window) override {

        sf::Vector2f p = shape.getPosition();

        // Main rock body
        sf::ConvexShape rock;
        rock.setPointCount(7);

        rock.setPoint(0, sf::Vector2f(8, 15));
        rock.setPoint(1, sf::Vector2f(20, 2));
        rock.setPoint(2, sf::Vector2f(38, 7));
        rock.setPoint(3, sf::Vector2f(49, 23));
        rock.setPoint(4, sf::Vector2f(42, 43));
        rock.setPoint(5, sf::Vector2f(17, 49));
        rock.setPoint(6, sf::Vector2f(2, 32));

        rock.setFillColor(sf::Color(100, 110, 125));
        rock.setOutlineThickness(2.f);
        rock.setOutlineColor(sf::Color(65, 75, 90));
        rock.setPosition(p);

        window.draw(rock);

        // Highlight
        sf::ConvexShape highlight;
        highlight.setPointCount(3);

        highlight.setPoint(0, sf::Vector2f(8, 15));
        highlight.setPoint(1, sf::Vector2f(20, 2));
        highlight.setPoint(2, sf::Vector2f(28, 13));

        highlight.setFillColor(sf::Color(155, 165, 180));
        highlight.setPosition(p);

        window.draw(highlight);
    }
};


// =====================================
// REEF
// =====================================

class Reef : public Obstacle {
public:
    Reef(sf::Vector2f pos, int damage = 10)
    : Obstacle(
        sf::Vector2f(90, 30),
        pos,
        sf::Color(220, 110, 80),
        damage
    ) {}
    
    void draw(sf::RenderWindow& window) override {

        sf::Vector2f p = shape.getPosition();

        // Coral base
        sf::RectangleShape base(
            sf::Vector2f(72, 12)
        );

        base.setPosition(p.x + 9, p.y + 16);
        base.setFillColor(sf::Color(190, 75, 75));

        window.draw(base);

        // Coral branches
        for (int i = 0; i < 5; i++) {

            sf::ConvexShape branch;
            branch.setPointCount(4);

            branch.setPoint(0, sf::Vector2f(0, 14));
            branch.setPoint(1, sf::Vector2f(3, 0));
            branch.setPoint(2, sf::Vector2f(9, 0));
            branch.setPoint(3, sf::Vector2f(12, 14));

            branch.setPosition(
                p.x + 8 + i * 16,
                p.y + (i % 2 == 0 ? 0.f : 5.f)
            );

            branch.setFillColor(
                i % 2 == 0
                    ? sf::Color(245, 115, 105)
                    : sf::Color(235, 145, 105)
            );

            window.draw(branch);
        }
    }
};