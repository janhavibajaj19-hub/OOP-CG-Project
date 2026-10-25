#pragma once
#include <cmath>
#include "GameObject.h"

class Ship : public GameObject {
private:
    int health;
    float fuel;
    int score;
    float speed;
    float fuelDrainRate;
    float hitCooldown;
public:
    Ship(
    float movementSpeed = 200.f,
    float fuelDrainRate = 4.f
)
    : GameObject(
        sf::Vector2f(60, 30),
        sf::Vector2f(30, 285),
        sf::Color::Transparent
    ),
    health(100),
    fuel(100.f),
    score(0),
    speed(movementSpeed),
    fuelDrainRate(fuelDrainRate),
    hitCooldown(0.f) {}

    // Draw the ship using custom shapes
    void draw(sf::RenderWindow& window) override {
        sf::Vector2f p = shape.getPosition();

        // Water wake behind the ship
        sf::ConvexShape wake;
        wake.setPointCount(4);

        wake.setPoint(0, sf::Vector2f(0.f, 5.f));
        wake.setPoint(1, sf::Vector2f(-24.f, 0.f));
        wake.setPoint(2, sf::Vector2f(-34.f, 15.f));
        wake.setPoint(3, sf::Vector2f(0.f, 25.f));

        wake.setFillColor(sf::Color(180, 230, 255, 100));
        wake.setPosition(p.x, p.y);

        window.draw(wake);             

        // Ship hull
        sf::ConvexShape hull;
        hull.setPointCount(5);

        hull.setPoint(0, sf::Vector2f(0, 0));
        hull.setPoint(1, sf::Vector2f(60, 0));
        hull.setPoint(2, sf::Vector2f(48, 30));
        hull.setPoint(3, sf::Vector2f(12, 30));
        hull.setPoint(4, sf::Vector2f(0, 15));

        hull.setFillColor(sf::Color(120, 65, 35));
        hull.setOutlineThickness(2.f);
        hull.setOutlineColor(sf::Color(75, 40, 20));
        hull.setPosition(p);

        window.draw(hull);

        // Mast
        sf::RectangleShape mast(sf::Vector2f(3, 29));
        mast.setFillColor(sf::Color(65, 40, 25));
        mast.setPosition(p.x + 27, p.y - 17);

        window.draw(mast);

        // Sail
        sf::ConvexShape sail;
        sail.setPointCount(3);

        sail.setPoint(0, sf::Vector2f(0, 0));
        sail.setPoint(1, sf::Vector2f(0, 24));
        sail.setPoint(2, sf::Vector2f(20, 24));

        sail.setFillColor(sf::Color(255, 245, 210));
        sail.setOutlineThickness(1.f);
        sail.setOutlineColor(sf::Color(180, 160, 120));
        sail.setPosition(p.x + 29, p.y - 17);

        window.draw(sail);
    }

    // Ship movement
    void update(float dt) override {
        sf::Vector2f dir(0.f, 0.f);

        if (fuel > 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                dir.x -= 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                dir.x += 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                dir.y -= 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                dir.y += 1;
        }

        // Prevent diagonal movement from being faster
        if (dir.x != 0.f || dir.y != 0.f) {
            float length = std::sqrt(
                dir.x * dir.x + dir.y * dir.y
            );

            dir.x /= length;
            dir.y /= length;

            shape.move(dir * speed * dt);

            fuel -= fuelDrainRate * dt;

            if (fuel < 0.f)
                fuel = 0.f;
        }

        if (hitCooldown > 0.f)
            hitCooldown -= dt;

        keepInsideScreen();
    }

    // Weather current movement
    void push(sf::Vector2f amount) {
        shape.move(amount);
        keepInsideScreen();
    }

    // Collision damage
    void takeDamage(int d) {
        if (hitCooldown > 0.f)
            return;

        health -= d;

        if (health < 0)
            health = 0;

        hitCooldown = 1.f;
    }

    // Gradual health drain, independent of collision cooldown
void drainHealth(int amount) {
    health -= amount;

    if (health < 0)
        health = 0;
}

    // Resource collection
    void addFuel(float f) {
        fuel += f;

        if (fuel > 100.f)
            fuel = 100.f;
    }

    void addScore(int s) {
        score += s;
    }

    // Getters
    int getHealth() const {
        return health;
    }

    float getFuel() const {
        return fuel;
    }

    int getScore() const {
        return score;
    }

    bool isAlive() const {
        return health > 0 && fuel > 0;
    }

        // Prepare the ship for the next level
    void prepareForNextLevel(float newSpeed, float newFuelDrain) {
        speed = newSpeed;
        fuelDrainRate = newFuelDrain;
        hitCooldown = 0.f;

        // Move ship back to the starting position
        shape.setPosition(30.f, 285.f);
    }

private:
    void keepInsideScreen() {
        sf::Vector2f p = shape.getPosition();

        if (p.x < 0.f)
            p.x = 0.f;

        if (p.x > 740.f)
            p.x = 740.f;

        if (p.y < 130.f)
            p.y = 130.f;

        if (p.y > 570.f)
            p.y = 570.f;

        shape.setPosition(p);
    }
};