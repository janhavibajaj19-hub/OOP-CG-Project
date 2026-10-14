#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include <cmath>

#include "Ship.h"
#include "Obstacle.h"
#include "Resource.h"
#include "Destination.h"
#include "Weather.h"

class Game {
private:

   enum class State
    {
    MainMenu,
    HowToPlay,
    Difficulty,
    Playing,
    Won,
    Lost
};

    // Window
    sf::RenderWindow window{
        sf::VideoMode(800, 600),
        "Ocean Adventure"
    };

    // Game objects
    Ship ship;
    Destination destination;

    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<Resource>> resources;

    // Weather
    std::vector<std::unique_ptr<Weather>> weatherTypes;

    Weather* weather = nullptr;

    float weatherTimer = 0.f;
    int weatherIndex = 0;

    // Game state
    State state = State::MainMenu;

    // Difficulty settings
    enum class Difficulty {
    Easy,
    Medium,
    Hard
    };

Difficulty difficulty = Difficulty::Medium;

    // Font and text
    sf::Font font;

    // Main Menu
    sf::Text titleText;
    sf::Text playText;
    sf::Text howToPlayText;
    sf::Text difficultyText;
    sf::Text exitText;

    // How to Play screen
    sf::Text instructionsTitle;
    sf::Text instructionsText;
    sf::Text backText;

    // Difficulty screen
    sf::Text difficultyTitle;
    sf::Text easyText;
    sf::Text mediumText;
    sf::Text hardText;          

    sf::RectangleShape menuBackground;
    sf::RectangleShape menuPanel;

    sf::Text healthText;
    sf::Text fuelText;
    sf::Text scoreText;
    sf::Text weatherText;
    sf::Text messageText;
    sf::Text scoreMessageText;
    sf::Text restartText;

    // HUD bars
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;
    sf::RectangleShape fuelBarBackground;
    sf::RectangleShape fuelBar;

    // Ocean animation
    float waveTime = 0.f;

    // Overlay
    sf::RectangleShape overlay;
    sf::RectangleShape messageBox;


    // =====================================
    // INITIALIZE TEXT
    // =====================================

    void setupText(
        sf::Text& text,
        unsigned int size,
        sf::Color color
    ) {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
    }


    // =====================================
    // INITIALIZE HUD
    // =====================================

    void setupHUD() {

        setupText(
            healthText,
            22,
            sf::Color::White
        );

        setupText(
            fuelText,
            22,
            sf::Color::White
        );

        setupText(
            scoreText,
            22,
            sf::Color(255, 210, 70)
        );

        setupText(
            weatherText,
            20,
            sf::Color(190, 220, 255)
        );

        setupText(
            messageText,
            36,
            sf::Color(70, 255, 170)
        );

        setupText(
            scoreMessageText,
            27,
            sf::Color(255, 210, 70)
        );

        setupText(
            restartText,
            21,
            sf::Color(210, 225, 245)
        );


        // Health bar background
        healthBarBackground.setSize(
            sf::Vector2f(250.f, 14.f)
        );

        healthBarBackground.setPosition(
            30.f, 105.f
        );

        healthBarBackground.setFillColor(
            sf::Color(35, 45, 65)
        );

        healthBarBackground.setOutlineThickness(1.f);

        healthBarBackground.setOutlineColor(
            sf::Color::White
        );


       // Health bar
        healthBar.setSize(
            sf::Vector2f(250.f, 14.f)
        );
 
        healthBar.setPosition(
            30.f, 105.f
        );

        healthBar.setFillColor(
            sf::Color(45, 220, 110)
        );


        // Fuel bar background
        fuelBarBackground.setSize(
            sf::Vector2f(250.f, 14.f)
        );

        fuelBarBackground.setPosition(
            310.f, 105.f
        );

        fuelBarBackground.setFillColor(
            sf::Color(35, 45, 65)
        );

        fuelBarBackground.setOutlineThickness(1.f);

        fuelBarBackground.setOutlineColor(
            sf::Color::White 
        );


        // Fuel bar
        fuelBar.setPosition(
            310.f, 105.f
        );

        fuelBar.setFillColor(
            sf::Color(55, 190, 255)
        );


        // End-game overlay
        overlay.setSize(
            sf::Vector2f(800.f, 600.f)
        );

        overlay.setFillColor(
            sf::Color(0, 10, 30, 175)
        );


        // End-game message box
        messageBox.setSize(
            sf::Vector2f(660.f, 400.f)
        );

        messageBox.setPosition(
            70.f, 100.f
        );

        messageBox.setFillColor(
            sf::Color(16, 38, 68)
        );

        messageBox.setOutlineThickness(3.f);

        messageBox.setOutlineColor(
            sf::Color(60, 230, 170)
        );
    }

    // =====================================
// SETUP MAIN MENU
// =====================================

void setupMainMenu() {

    // Ocean background
    menuBackground.setSize(sf::Vector2f(800.f, 600.f));
    menuBackground.setFillColor(sf::Color(8, 35, 75));

    // Central menu panel
    menuPanel.setSize(sf::Vector2f(720.f, 470.f));
    menuPanel.setPosition(40.f, 70.f);
    menuPanel.setFillColor(sf::Color(15, 55, 95, 245));
    menuPanel.setOutlineThickness(2.f);
    menuPanel.setOutlineColor(sf::Color(80, 210, 240));

    // Game title
    setupText(titleText, 42, sf::Color(255, 220, 120));
    titleText.setString("OCEAN ADVENTURE");

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(
        titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f
    );
    titleText.setPosition(400.f, 190.f);

    // Menu options
    setupText(playText, 27, sf::Color::White);
    setupText(howToPlayText, 24, sf::Color::White);
    setupText(difficultyText, 24, sf::Color::White);
    setupText(exitText, 24, sf::Color(255, 150, 150));

    playText.setString("PLAY");
    howToPlayText.setString("HOW TO PLAY");
    difficultyText.setString("DIFFICULTY");
    exitText.setString("EXIT");

    playText.setPosition(350.f, 270.f);
    howToPlayText.setPosition(315.f, 330.f);
    difficultyText.setPosition(330.f, 385.f);
    exitText.setPosition(370.f, 440.f);

    // Center the menu options
auto centerText = [](sf::Text& text, float y) {
    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    text.setPosition(400.f, y);
};

centerText(playText, 270.f);
centerText(howToPlayText, 330.f);
centerText(difficultyText, 385.f);
centerText(exitText, 440.f);
}


    void setupExtraScreens() {

    // How to Play
    setupText(instructionsTitle, 34, sf::Color(255, 220, 120));
    instructionsTitle.setString("HOW TO PLAY");
    instructionsTitle.setPosition(400.f, 95.f);

    setupText(instructionsText, 16, sf::Color::White);
    instructionsText.setString(
        "MISSION: Reach the destination and survive!\n\n"
        "CONTROLS\n"
        "Arrow Keys - Move your ship\n"
        "R - Restart after victory or defeat\n\n"
        "SCORING\n"
        "Treasure chest: +50 points each\n"
        "Reach destination: +100 points\n"
        "Health above 50 at finish: +25 bonus\n"
        "Fuel above 25 at finish: +25 bonus\n"
        "Fuel barrels restore fuel but give no points\n\n"
        "SURVIVAL\n"
        "Rocks deal 20 damage; reefs deal 10 damage.\n"
        "Fuel drains while you move.\n"
        "Weather can push your ship with currents.\n"
        "Health or fuel reaching zero means game over."
    );
    instructionsText.setPosition(100.f, 175.f);

    setupText(backText, 23, sf::Color(255, 220, 120));
    backText.setString("< BACK TO MENU");
    backText.setPosition(40.f, 550.f);

    // Difficulty selection
    setupText(difficultyTitle, 36, sf::Color(255, 220, 120));
    difficultyTitle.setString("SELECT DIFFICULTY");

    sf::FloatRect titleBounds = difficultyTitle.getLocalBounds();
    difficultyTitle.setOrigin(
        titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f
    );
    difficultyTitle.setPosition(400.f, 180.f);

    setupText(easyText, 28, sf::Color::White);
    setupText(mediumText, 28, sf::Color::White);
    setupText(hardText, 28, sf::Color::White);

    easyText.setString("EASY");
    mediumText.setString("MEDIUM");
    hardText.setString("HARD");

    easyText.setPosition(350.f, 260.f);
    mediumText.setPosition(335.f, 325.f);
    hardText.setPosition(355.f, 390.f);
}

    // =====================================
    // INITIALIZE GAME OBJECTS
    // =====================================

    void createObjects() {

        obstacles.clear();
        resources.clear();

        int rockDamage = 20;
int reefDamage = 10;

if (difficulty == Difficulty::Easy) {
    rockDamage = 10;
    reefDamage = 5;
}
else if (difficulty == Difficulty::Hard) {
    rockDamage = 35;
    reefDamage = 20;
}

        // Rocks
        obstacles.push_back(
    std::make_unique<Rock>(
        sf::Vector2f(535.f, 200.f),
        rockDamage
        )
    );

        obstacles.push_back(
            std::make_unique<Rock>(
                sf::Vector2f(340.f, 485.f),
                rockDamage
            )
        );

        obstacles.push_back(
            std::make_unique<Rock>(
                sf::Vector2f(120.f, 165.f),
                rockDamage
            )
        );

        obstacles.push_back(
            std::make_unique<Rock>(
                sf::Vector2f(580.f, 150.f),
                rockDamage
            )
        );


        // Reefs
        obstacles.push_back(
            std::make_unique<Reef>(
                sf::Vector2f(460.f, 315.f),
                reefDamage
            )
        );

        obstacles.push_back(
            std::make_unique<Reef>(
                sf::Vector2f(690.f, 545.f),
                reefDamage
            )
        );


        // Fuel resources
        resources.push_back(
            std::make_unique<Fuel>(
                sf::Vector2f(170.f, 350.f)
            )
        );

        resources.push_back(
            std::make_unique<Fuel>(
                sf::Vector2f(320.f, 400.f)
            )
        );

        resources.push_back(
            std::make_unique<Fuel>(
                sf::Vector2f(650.f, 175.f)
            )
        );


        // Treasure resources
        resources.push_back(
            std::make_unique<Treasure>(
                sf::Vector2f(400.f, 190.f)
            )
        );

        resources.push_back(
            std::make_unique<Treasure>(
                sf::Vector2f(660.f, 330.f)
            )
        );
    }


    // =====================================
    // UPDATE HUD
    // =====================================

    void updateHUD() {

        healthText.setString(
            "HEALTH: " +
            std::to_string(ship.getHealth())
        );

        healthText.setPosition(40.f, 40.f);


        fuelText.setString(
    "FUEL: " + std::to_string(
        static_cast<int>(ship.getFuel())
         )
    );

        fuelText.setPosition(310.f, 40.f);


        scoreText.setString(
            "SCORE: " +
            std::to_string(ship.getScore())
        );

        scoreText.setPosition(575.f, 40.f);


        if (weather != nullptr) {

            weatherText.setString(
                "Weather: " + weather->getName()
            );

        }

        weatherText.setPosition(310.f, 75.f);


        // Health bar
        float healthRatio =
            static_cast<float>(ship.getHealth()) / 100.f;

        if (healthRatio < 0.f)
            healthRatio = 0.f;

        if (healthRatio > 1.f)
            healthRatio = 1.f;

        healthBar.setSize(
            sf::Vector2f(
                250.f * healthRatio,
                14.f
            )
        );


        if (healthRatio > 0.5f) {

            healthBar.setFillColor(
                sf::Color(45, 220, 110)
            );

        }
        else {

            healthBar.setFillColor(
                sf::Color(240, 75, 75)
            );

        }


        // Fuel bar
        float fuelRatio =
            static_cast<float>(ship.getFuel()) / 100.f;

        if (fuelRatio < 0.f)
            fuelRatio = 0.f;

        if (fuelRatio > 1.f)
            fuelRatio = 1.f;

        fuelBar.setSize(
            sf::Vector2f(
                250.f * fuelRatio,
                14.f
            )
        );
    }
    
    // =====================================
// PROCESS EVENTS
// =====================================

void processEvents() {

    sf::Event event;

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2f mousePosition(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
            );

            if (state == State::MainMenu) {

                if (playText.getGlobalBounds().contains(mousePosition)) {
                    reset();
                }
                else if (howToPlayText.getGlobalBounds().contains(mousePosition)) {
                    state = State::HowToPlay;
                }
                else if (difficultyText.getGlobalBounds().contains(mousePosition)) {
                    state = State::Difficulty;
                }
                else if (exitText.getGlobalBounds().contains(mousePosition)) {
                    window.close();
                }
            }
            else if (state == State::HowToPlay) {

                if (backText.getGlobalBounds().contains(mousePosition)) {
                    state = State::MainMenu;
                }
            }
            else if (state == State::Difficulty) {

                if (backText.getGlobalBounds().contains(mousePosition)) {
                    state = State::MainMenu;
                }
                else if (easyText.getGlobalBounds().contains(mousePosition)) {
                difficulty = Difficulty::Easy;
                reset();
}
                else if (mediumText.getGlobalBounds().contains(mousePosition)) {
                    difficulty = Difficulty::Medium;
                    reset();
                }
                else if (hardText.getGlobalBounds().contains(mousePosition)) {
                    difficulty = Difficulty::Hard;
                    reset();
                        }
                            }
                        }

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::R &&
                (state == State::Won || state == State::Lost)) {
                reset();
            }

            if (event.key.code == sf::Keyboard::Escape &&
                (state == State::HowToPlay || state == State::Difficulty)) {
                state = State::MainMenu;
            }
        }
    }
}
    // =====================================
    // UPDATE GAME
    // =====================================

    void update(float dt) {

        // Stop gameplay after winning or losing
        if (state != State::Playing) {
            return;
        }


        // Update ocean animation
        waveTime += dt;


        // Update weather
        weatherTimer += dt;

        if (weatherTimer >= 8.f) {

            weatherTimer = 0.f;

            weatherIndex =
                (weatherIndex + 1) %
                static_cast<int>(weatherTypes.size());

            weather = weatherTypes[weatherIndex].get();

        }


        // Ship movement
        ship.update(dt);


        // Weather currents
        if (weather != nullptr) {

            ship.push(
                weather->getCurrent() * dt
            );

        }

        // Keep the ship below the HUD
        sf::FloatRect shipBox = ship.getBounds();
        if (shipBox.top < 125.f) {
            ship.push(sf::Vector2f(0.f, 125.f - shipBox.top));
        }


        // =====================================
        // OBSTACLE COLLISIONS
        // =====================================

        for (auto& obstacle : obstacles) {

            if (
                ship.getBounds().intersects(
                    obstacle->getBounds()
                )
            ) {

                ship.takeDamage(
                    obstacle->getDamage()
                );

            }

        }


        // =====================================
        // RESOURCE COLLECTION
        // =====================================

        for (auto& resource : resources) {

            if (
                !resource->isCollected() &&
                ship.getBounds().intersects(
                    resource->getBounds()
                )
            ) {

                resource->collect(ship);

            }

        }


        // =====================================
        // WIN / LOSE CONDITIONS
        // =====================================

        // Win only after reaching the destination
        if (
            ship.getBounds().intersects(
                destination.getBounds()
            )
        ) {

            // Destination bonus
            ship.addScore(100);


            // Health bonus
            if (ship.getHealth() > 50) {

                ship.addScore(25);

            }


            // Fuel bonus
            if (ship.getFuel() > 25) {

                ship.addScore(25);

            }


            state = State::Won;

        }
        else if (!ship.isAlive()) {

            state = State::Lost;

        }


        // Refresh HUD
        updateHUD();
    }


    // =====================================
    // DRAW OCEAN
    // =====================================

    void drawOcean() {

        sf::RectangleShape ocean(
            sf::Vector2f(800.f, 600.f)
        );

        if (weather != nullptr) {

            ocean.setFillColor(
                weather->getSkyColor()
            );

        }
        else {

            ocean.setFillColor(
                sf::Color(12, 65, 125)
            );

        }

        window.draw(ocean);


        // Animated wave lines
        for (int i = 0; i < 9; i++) {

            sf::VertexArray wave(
                sf::LineStrip,
                81
            );

            float baseY =
                145.f + i * 55.f;

            for (int j = 0; j <= 80; j++) {

                float x =
                    static_cast<float>(j) * 10.f;

                float y =
                    baseY +
                    std::sin(
                        x * 0.015f +
                        waveTime * 1.5f +
                        i
                    ) * 5.f;

                wave[j].position =
                    sf::Vector2f(x, y);

                wave[j].color =
                    sf::Color(130, 205, 255, 100);

            }

            window.draw(wave);

        }


        // Small moving water highlights
        for (int i = 0; i < 12; i++) {

            float x =
                std::fmod(
                    i * 137.f + waveTime * 35.f,
                    800.f
                );

            float y =
                150.f +
                std::fmod(i * 67.f, 420.f);

            sf::RectangleShape highlight(
                sf::Vector2f(24.f, 3.f)
            );

            highlight.setPosition(x, y);

            highlight.setFillColor(
                sf::Color(175, 225, 255, 120)
            );

            window.draw(highlight);

        }

        // Second layer of ocean waves
for (int i = 0; i < 6; i++) {
    sf::VertexArray wave(sf::LineStrip, 61);

    float baseY = 165.f + i * 65.f;

    for (int j = 0; j <= 60; j++) {
        float x = j * 13.3f;

        float y = baseY +
            std::sin(x * 0.025f - waveTime * 0.8f + i * 1.5f) * 3.f;

        wave[j].position = sf::Vector2f(x, y);
        wave[j].color = sf::Color(80, 175, 220, 65);
    }

    window.draw(wave);
}

    }


    // =====================================
    // DRAW HUD
    // =====================================

    void drawHUD() {

        sf::RectangleShape hudBackground(
            sf::Vector2f(800.f, 125.f)
        );

        hudBackground.setFillColor(
            sf::Color(15, 40, 75)
        );

        window.draw(hudBackground);


        window.draw(healthText);
        window.draw(fuelText);
        window.draw(scoreText);
        window.draw(weatherText);

        window.draw(healthBarBackground);
        window.draw(healthBar);

        window.draw(fuelBarBackground);
        window.draw(fuelBar);

    }


    // =====================================
    // DRAW END SCREEN
    // =====================================

    void drawEndScreen() {

        window.draw(overlay);
        window.draw(messageBox);


        if (state == State::Won) {

            messageText.setString(
                "VOYAGE COMPLETE!"
            );

        }
        else {

            messageText.setString(
                "VOYAGE FAILED!"
            );

        }


        sf::FloatRect messageBounds =
            messageText.getLocalBounds();

        messageText.setOrigin(
            messageBounds.left +
                messageBounds.width / 2.f,

            messageBounds.top +
                messageBounds.height / 2.f
        );

        messageText.setPosition(
            400.f, 205.f
        );


        scoreMessageText.setString(
            "Your Score: " +
            std::to_string(ship.getScore())
        );

        sf::FloatRect scoreBounds =
            scoreMessageText.getLocalBounds();

        scoreMessageText.setOrigin(
            scoreBounds.left +
                scoreBounds.width / 2.f,

            scoreBounds.top +
                scoreBounds.height / 2.f
        );

        scoreMessageText.setPosition(
            400.f, 315.f
        );


        restartText.setString(
            "Press R to play again"
        );

        sf::FloatRect restartBounds =
            restartText.getLocalBounds();

        restartText.setOrigin(
            restartBounds.left +
                restartBounds.width / 2.f,

            restartBounds.top +
                restartBounds.height / 2.f
        );

        restartText.setPosition(
            400.f, 400.f
        );


        window.draw(messageText);
        window.draw(scoreMessageText);
        window.draw(restartText);

    }
    
    // =====================================
// DRAW MAIN MENU
// =====================================

void drawMainMenu() {
    window.draw(menuBackground);

    // Decorative ocean waves
    for (int i = 0; i < 8; i++) {
        sf::RectangleShape wave(sf::Vector2f(800.f, 2.f));

        wave.setPosition(
            0.f,
            60.f + i * 70.f
        );

        wave.setFillColor(
            sf::Color(60, 150, 210, 70)
        );

        window.draw(wave);
    }

    window.draw(menuPanel);
    window.draw(titleText);
    window.draw(playText);
    window.draw(howToPlayText);
    window.draw(difficultyText);
    window.draw(exitText);
}


// =====================================
// DRAW HOW TO PLAY
// =====================================

void drawHowToPlay() {
    window.draw(menuBackground);

    window.draw(menuPanel);
    window.draw(instructionsTitle);
    window.draw(instructionsText);
    window.draw(backText);
}


// =====================================
// DRAW DIFFICULTY SCREEN
// =====================================

void drawDifficultyScreen() {
    window.draw(menuBackground);

    window.draw(menuPanel);
    window.draw(difficultyTitle);
    window.draw(easyText);
    window.draw(mediumText);
    window.draw(hardText);
    window.draw(backText);
}

    // =====================================
    // RENDER
    // =====================================

    void render() {

    window.clear();

    // MAIN MENU
    if (state == State::MainMenu) {
        drawMainMenu();
    }

    // HOW TO PLAY
    else if (state == State::HowToPlay) {
        drawHowToPlay();
    }

    // DIFFICULTY SELECTION
    else if (state == State::Difficulty) {
        drawDifficultyScreen();
    }

    // GAMEPLAY, VICTORY AND DEFEAT
    else {

        // Ocean background
        drawOcean();

        // Destination
        destination.draw(window);

        // Obstacles
        for (auto& obstacle : obstacles) {
            obstacle->draw(window);
        }

        // Resources
        for (auto& resource : resources) {
            resource->draw(window);
        }

        // Ship
        ship.draw(window);

        // HUD
        drawHUD();

        // End screen
        if (state == State::Won ||
            state == State::Lost) {
            drawEndScreen();
        }
    }

    window.display();
}

public:

    // =====================================
    // CONSTRUCTOR
    // =====================================

    Game() {

        window.setFramerateLimit(60);


        // Load font
        if (
            !font.loadFromFile(
                "C:/Windows/Fonts/arial.ttf"
            )
        ) {

            // Font loading failed.
            // Replace this path if necessary.

        }


        // Weather types
        weatherTypes.push_back(
            std::make_unique<Sunny>()
        );

        weatherTypes.push_back(
            std::make_unique<Rain>()
        );

        weatherTypes.push_back(
            std::make_unique<Storm>()
        );


        weather = weatherTypes[0].get();


        // HUD
        setupHUD();

        // Main menu
        setupMainMenu();

        setupExtraScreens();


        // Create objects
        createObjects();


        // Initial HUD values
        updateHUD();

    }


    // =====================================
    // RESET GAME
    // =====================================

    void reset() {

        state = State::Playing;

        weatherTimer = 0.f;
        weatherIndex = 0;

        waveTime = 0.f;

        weather = weatherTypes[0].get();


        // Reset ship
        float speed = 200.f;
        float fuelDrain = 4.f;

           if (difficulty == Difficulty::Easy) {
           fuelDrain = 2.f;
        }
        else if (difficulty == Difficulty::Hard) {

           fuelDrain = 7.f;
        }

ship = Ship(speed, fuelDrain);


        // Reset game objects
        createObjects();


        // Reset HUD
        updateHUD();

    }


    // =====================================
    // MAIN GAME LOOP
    // =====================================

    void run() {

        sf::Clock clock;

        while (window.isOpen()) {

            float dt =
                clock.restart().asSeconds();


            // Prevent huge time jumps
            if (dt > 0.05f) {

                dt = 0.05f;

            }


            processEvents();

            update(dt);

            render();

        }

    }

};