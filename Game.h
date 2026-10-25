#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>

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
    Playing,
    LevelComplete,
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
    // Passive health drain
float healthDrainTimer = 0.f;

    // Game state
    State state = State::MainMenu;
    // Level progression
    int currentLevel = 1;
    const int maxLevels = 5;

    // Random number generator
    std::mt19937 rng{ std::random_device{}() };

   
    // Font and text
    sf::Font font;

    // Main Menu
    sf::Text titleText;
    sf::Text playText;
    sf::Text howToPlayText;
    sf::Text exitText;

    // How to Play screen
    sf::Text instructionsTitle;
    sf::Text instructionsText;
    sf::Text backText;
       

    sf::RectangleShape menuBackground;
    sf::RectangleShape menuPanel;

    sf::Text healthText;
    sf::Text fuelText;
    sf::Text scoreText;
    sf::Text weatherText;
    sf::Text levelText;

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

    sf::RectangleShape restartButton;
    sf::Text restartButtonText;

    // Level completion screen
sf::RectangleShape nextLevelButton;
sf::Text nextLevelButtonText;
sf::Text levelCompleteText;


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

        // Level number text
        setupText(
            levelText, 20, sf::Color(255, 220, 120));
            levelText.setPosition(310.f, 25.f);

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
// UPDATE HUD VALUES
// =====================================

void updateHUD() {
    // Update health text
    // Update current level
levelText.setString(
    "LEVEL: " + std::to_string(currentLevel)
);

    healthText.setString(
        "Health: " + std::to_string(ship.getHealth())
    );
    healthText.setPosition(30.f, 65.f);

    // Update fuel text
    fuelText.setString(
        "Fuel: " + std::to_string(
            static_cast<int>(ship.getFuel())
        )
    );
    fuelText.setPosition(310.f, 65.f);

    // Update score text
    scoreText.setString(
        "Score: " + std::to_string(ship.getScore())
    );
    scoreText.setPosition(590.f, 65.f);

    // Update weather text
    if (weather != nullptr) {
        weatherText.setString(
            "Weather: " + weather->getName()
        );
    }
    else {
        weatherText.setString("Weather: Sunny");
    }
    weatherText.setPosition(590.f, 25.f);

    // Update health bar
    float healthWidth =
        250.f * ship.getHealth() / 100.f;

    healthBar.setSize(
        sf::Vector2f(healthWidth, 14.f)
    );

    // Update fuel bar
    float fuelWidth =
        250.f * ship.getFuel() / 100.f;

    fuelBar.setSize(
        sf::Vector2f(fuelWidth, 14.f)
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
    setupText(exitText, 24, sf::Color(255, 150, 150));

    playText.setString("PLAY");
    howToPlayText.setString("HOW TO PLAY");
    exitText.setString("EXIT");

    playText.setPosition(400.f, 290.f);
    howToPlayText.setPosition(400.f, 355.f);
    exitText.setPosition(400.f, 420.f);

    // Center the menu options
    auto centerText = [](sf::Text& text, float y) {
    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    text.setPosition(400.f, y);
};

centerText(playText, 290.f);
centerText(howToPlayText, 355.f);
centerText(exitText, 420.f);
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
}


    // Generate random positions for game objects
sf::Vector2f randomPosition(float objectWidth, float objectHeight) {
    std::uniform_real_distribution<float> xDist(
        80.f, 720.f - objectWidth
    );

    std::uniform_real_distribution<float> yDist(
        145.f, 570.f - objectHeight
    );

    return sf::Vector2f(xDist(rng), yDist(rng));
}

    
 // =====================================
// INITIALIZE GAME OBJECTS
// =====================================

void createObjects() {
    obstacles.clear();
    resources.clear();

    // Obstacle damage increases with each level
    int rockDamage = 20 + (currentLevel - 1) * 5;
    int reefDamage = 10 + (currentLevel - 1) * 3;

    // Store occupied areas to prevent objects from overlapping
    std::vector<sf::FloatRect> occupiedAreas;

    // Keep the ship's starting area clear
    occupiedAreas.emplace_back(0.f, 125.f, 150.f, 220.f);

    // Keep the destination area clear
    occupiedAreas.emplace_back(700.f, 220.f, 100.f, 180.f);

    // Check whether a new object overlaps an existing object
    auto overlapsExisting = [&](const sf::FloatRect& candidate) {
        for (const auto& area : occupiedAreas) {
            if (candidate.intersects(area)) {
                return true;
            }
        }
        return false;
    };

    // Find a random position that doesn't overlap existing objects
    auto findPosition = [&](float width, float height) {
        for (int attempt = 0; attempt < 200; attempt++) {
            sf::Vector2f pos = randomPosition(width, height);

            sf::FloatRect candidate(
                pos.x - 8.f,
                pos.y - 8.f,
                width + 16.f,
                height + 16.f
            );

            if (!overlapsExisting(candidate)) {
                occupiedAreas.push_back(candidate);
                return pos;
            }
        }

        // Fallback if no suitable position is found
        return randomPosition(width, height);
    };

    // Increase obstacle count at each level
    int rockCount = 3 + currentLevel;
    int reefCount = 1 + currentLevel;

    // Create rocks
    for (int i = 0; i < rockCount; i++) {
        sf::Vector2f pos = findPosition(35.f, 35.f);

        obstacles.push_back(
            std::make_unique<Rock>(pos, rockDamage)
        );
    }

    // Create reefs
    for (int i = 0; i < reefCount; i++) {
        sf::Vector2f pos = findPosition(50.f, 25.f);

        obstacles.push_back(
            std::make_unique<Reef>(pos, reefDamage)
        );
    }

    // Create fuel pickups
    int fuelCount = 3;

    for (int i = 0; i < fuelCount; i++) {
        sf::Vector2f pos = findPosition(25.f, 25.f);

        resources.push_back(
            std::make_unique<Fuel>(pos)
        );
    }

    // Create treasures
    int treasureCount = 2 + currentLevel / 2;

    for (int i = 0; i < treasureCount; i++) {
        sf::Vector2f pos = findPosition(25.f, 25.f);

        resources.push_back(
            std::make_unique<Treasure>(pos)
        );
    }
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

          // Victory and Game Over screen
if (state == State::Won || state == State::Lost) {

    if (restartButton.getGlobalBounds().contains(mousePosition)) {
        reset();
    }
}

// Level Complete screen
else if (state == State::LevelComplete) {

    if (nextLevelButton.getGlobalBounds().contains(mousePosition)) {

        currentLevel++;

        // Increase difficulty with each level
        float newSpeed = 200.f + (currentLevel - 1) * 20.f;
        float newFuelDrain = 3.f + (currentLevel - 1) * 0.5f;

        ship.prepareForNextLevel(newSpeed, newFuelDrain);

        weatherTimer = 0.f;
        healthDrainTimer = 0.f;
        weatherIndex = 0;
        weather = weatherTypes[0].get();

        createObjects();

        state = State::Playing;

        updateHUD();
    }
}

            if (state == State::MainMenu) {

                if (playText.getGlobalBounds().contains(mousePosition)) {
                    reset();
                }
                else if (howToPlayText.getGlobalBounds().contains(mousePosition)) {
                    state = State::HowToPlay;
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
           
                        }

        if (event.type == sf::Event::KeyPressed) {

if (event.key.code == sf::Keyboard::Escape &&
    state == State::HowToPlay) {
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

        if (weatherTimer >= 4.f) {

            weatherTimer = 0.f;

            weatherIndex =
                (weatherIndex + 1) %
                static_cast<int>(weatherTypes.size());

            weather = weatherTypes[weatherIndex].get();

        }


        // Ship movement
        ship.update(dt);

       // Gradual health drain increases with each level
healthDrainTimer += dt;

float healthDrainInterval = 6.f - currentLevel;

if (healthDrainTimer >= healthDrainInterval) {
    ship.drainHealth(1);
    healthDrainTimer = 0.f;
}


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

if (!ship.isAlive()) {
    state = State::Lost;
}
else if (ship.getBounds().intersects(destination.getBounds())) {

    if (currentLevel < maxLevels) {
        state = State::LevelComplete;
    }
    else {
        // Award final completion bonuses only once
        ship.addScore(100);

        if (ship.getHealth() > 50) {
            ship.addScore(25);
        }

        if (ship.getFuel() > 25) {
            ship.addScore(25);
        }

        state = State::Won;
    }
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
        window.draw(levelText);

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
            "Click RESTART to play again"
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
            400.f, 355.f
        );


        window.draw(messageText);
        window.draw(restartButton);
        window.draw(restartButtonText);
        window.draw(scoreMessageText);
        window.draw(restartText);

    }

    // =====================================
// DRAW LEVEL COMPLETE SCREEN
// =====================================

void drawLevelCompleteScreen() {
    window.draw(overlay);
    window.draw(messageBox);

    levelCompleteText.setString(
        "LEVEL " + std::to_string(currentLevel) + " COMPLETE!"
    );

    sf::FloatRect bounds = levelCompleteText.getLocalBounds();

    levelCompleteText.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    levelCompleteText.setPosition(400.f, 205.f);

    window.draw(levelCompleteText);

    window.draw(nextLevelButton);
    window.draw(nextLevelButtonText);

    scoreMessageText.setString(
        "Your Score: " + std::to_string(ship.getScore())
    );

    sf::FloatRect scoreBounds = scoreMessageText.getLocalBounds();

    scoreMessageText.setOrigin(
        scoreBounds.left + scoreBounds.width / 2.f,
        scoreBounds.top + scoreBounds.height / 2.f
    );

    scoreMessageText.setPosition(400.f, 300.f);

    window.draw(scoreMessageText);
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

       // Level Complete screen
if (state == State::LevelComplete) {
    drawLevelCompleteScreen();
}

// Victory and Game Over screens
else if (state == State::Won ||
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

        // Restart button
        restartButton.setSize(sf::Vector2f(180.f, 50.f));
        restartButton.setFillColor(sf::Color(30, 140, 100));
        restartButton.setPosition(310.f, 380.f);

        // Next Level button
nextLevelButton.setSize(sf::Vector2f(200.f, 50.f));
nextLevelButton.setFillColor(sf::Color(30, 140, 100));
nextLevelButton.setPosition(300.f, 380.f);

nextLevelButtonText.setFont(font);
nextLevelButtonText.setString("NEXT LEVEL");
nextLevelButtonText.setCharacterSize(22);
nextLevelButtonText.setFillColor(sf::Color::White);

sf::FloatRect nextBounds = nextLevelButtonText.getLocalBounds();

nextLevelButtonText.setOrigin(
    nextBounds.left + nextBounds.width / 2.f,
    nextBounds.top + nextBounds.height / 2.f
);

nextLevelButtonText.setPosition(400.f, 405.f);

// Level Complete message
setupText(levelCompleteText, 36, sf::Color(70, 255, 170));
levelCompleteText.setString("LEVEL COMPLETE!");

sf::FloatRect levelBounds = levelCompleteText.getLocalBounds();

levelCompleteText.setOrigin(
    levelBounds.left + levelBounds.width / 2.f,
    levelBounds.top + levelBounds.height / 2.f
);

levelCompleteText.setPosition(400.f, 205.f);

        restartButtonText.setFont(font);
        restartButtonText.setString("RESTART");
        restartButtonText.setCharacterSize(22);
        restartButtonText.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = restartButtonText.getLocalBounds();

        restartButtonText.setOrigin(
            textBounds.left + textBounds.width / 2.f,
            textBounds.top + textBounds.height / 2.f
        );

    restartButtonText.setPosition(400.f, 405.f);


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

    // Start a new game from Level 1
    currentLevel = 1;

    weatherTimer = 0.f;
    healthDrainTimer = 0.f;
    weatherIndex = 0;
    waveTime = 0.f;

    weather = weatherTypes[0].get();

    // Set ship properties for Level 1
    float speed = 200.f;
    float fuelDrain = 3.f;

    ship = Ship(speed, fuelDrain);

    // Generate game objects
    createObjects();

    // Refresh HUD
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