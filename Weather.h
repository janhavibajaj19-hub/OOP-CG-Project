#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Abstract class: defines WHAT every weather can do, not HOW.
class Weather {
public:
    virtual ~Weather() {}
    virtual std::string  getName() const = 0;
    virtual sf::Color    getSkyColor() const = 0;
    virtual sf::Vector2f getCurrent() const = 0;   // push on the ship (pixels/second)
};

class Sunny : public Weather {
public:
    std::string  getName() const override { return "Sunny"; }
    sf::Color    getSkyColor() const override { return sf::Color(30, 144, 255); }
    sf::Vector2f getCurrent() const override { return sf::Vector2f(0, 0); }
};

class Rain : public Weather {
public:
    std::string  getName() const override { return "Rain"; }
    sf::Color    getSkyColor() const override { return sf::Color(30, 90, 170); }
    sf::Vector2f getCurrent() const override { return sf::Vector2f(0, 40); }
};

class Storm : public Weather {
public:
    std::string  getName() const override { return "Storm"; }
    sf::Color    getSkyColor() const override { return sf::Color(15, 35, 80); }
    sf::Vector2f getCurrent() const override { return sf::Vector2f(-30, 90); }
};
