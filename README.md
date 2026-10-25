# 🌊 Ocean Adventure

**Ocean Adventure** is a 2D ocean-survival game developed in **C++ using SFML 2.6.1**. The player navigates a ship through an ocean, avoids obstacles, collects resources and treasure, and reaches the destination island while managing health and fuel.

The game features five progressive levels, randomized object placement, changing weather conditions, and increasing survival challenges.

## 🎮 Features

* **Five Progressive Levels:** Complete five levels with increasing difficulty.
* **Randomized Object Placement:** Rocks, reefs, fuel pickups, and treasure are placed at randomized positions when a level is generated.
* **Increasing Difficulty:** Obstacle quantities, collision damage, fuel consumption, and passive health depletion increase as the player progresses.
* **Animated Ocean:** An animated ocean background with moving waves and water highlights.
* **Weather System:** Sunny, rainy, and stormy conditions change the game's appearance.
* **Health and Fuel Management:** Monitor the ship's health and fuel throughout the voyage.
* **Resource Collection:** Collect fuel barrels to replenish fuel and treasure chests to earn points.
* **Collision Detection:** Collisions with rocks and reefs damage the ship.
* **Level Indicator:** Displays the current level during gameplay.
* **Level Progression:** Reach the destination to complete a level and unlock the next one.
* **Game States:** Includes a main menu, instructions screen, gameplay, level-completion screens, victory screen, and Game Over screen.
* **Restart Functionality:** Restart the game using the on-screen button after victory or defeat.

## 🌊 Level Progression

Ocean Adventure contains five levels. Each level increases the survival challenge by introducing more obstacles and increasing damage and resource-management demands.

| Level | Rocks | Reefs | Rock Damage | Reef Damage |
| :---: | ----: | ----: | ----------: | ----------: |
|   1   |     4 |     2 |          20 |          10 |
|   2   |     5 |     3 |          25 |          13 |
|   3   |     6 |     4 |          30 |          16 |
|   4   |     7 |     5 |          35 |          19 |
|   5   |     8 |     6 |          40 |          22 |

Additional difficulty changes include:

* Ship movement speed increases with each level.
* Fuel consumption increases with each level.
* Passive health depletion becomes more frequent, changing from once every five seconds in Level 1 to once every second in Level 5.
* Treasure quantities increase at certain levels.
* Object positions are randomized whenever a level's objects are generated.
* Three fuel pickups are generated per level.
* Weather conditions rotate every four seconds, independently of the current level.

These changes require the player to manage health and fuel carefully, especially in the later levels.

🏁 Completing a Level

To complete a level, navigate the ship to the destination.

Levels 1–4: A level-completion screen appears.
Next Level: Select the NEXT LEVEL button to continue.
Ship Position: The ship returns to its starting position at the beginning of the next level.
Health and Fuel: Remaining health and fuel carry over to the next level.
Difficulty: Movement speed and fuel consumption are adjusted for the next level.
Level 5: Reaching the destination triggers the final victory screen.

The game ends in defeat if the ship's health or fuel reaches zero.

⌨️ Controls
Input	Action
Arrow Keys	Move the ship
Mouse	Select menu options, advance to the next level, or restart after victory or defeat
Escape	Return to the main menu from the How to Play screen
🏆 Scoring System
Action	Points
Collect a treasure chest	+50
Complete the final level	+100
Finish the final level with health above 50	+25 bonus
Finish the final level with fuel above 25	+25 bonus

Additional details:

Fuel barrels restore fuel but do not directly increase the score.
The destination and completion bonuses are awarded at the end of Level 5, not after every level.
❤️ Survival Rules
Rocks and reefs damage the ship upon collision.
A one-second damage cooldown prevents repeated obstacle damage during that interval.
Fuel decreases while the ship is moving.
Fuel consumption increases with each level.
Passive health depletion becomes more frequent as the player progresses.
Weather conditions change during gameplay.
Fuel pickups restore fuel up to the ship's maximum capacity.
Obstacle quantity and damage increase with each level.
Reaching the destination completes the current level.
The game ends when health or fuel reaches zero.
Completing Level 5 triggers the final victory screen.
🛠️ Technologies Used
Programming Language: C++
Graphics and Game Library: SFML 2.6.1
Compiler: MinGW-w64
Code Editor: Visual Studio Code
Version Control: Git and GitHub
📁 Project Structure

The project is organized into separate source and header files for game management and game objects.

OceanAdventure/
├── main.cpp
├── Game.h
├── GameObject.h
├── Ship.h
├── Obstacle.h
├── Resource.h
├── Destination.h
├── Weather.h
└── README.md
⚙️ Setup and Execution
Prerequisites

Before running the game, make sure you have:

A C++ compiler, such as MinGW-w64.
SFML 2.6.1 installed and configured.
The SFML graphics, window, and system libraries.
The required SFML DLL files available when running the executable.
Compile

If SFML is installed in C:\SFML, open a terminal in the project directory and run:

g++ main.cpp -o OceanAdventure.exe -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system

If SFML is installed in a different location, update the include and library paths accordingly.

Run

After successful compilation, run the executable:

.\OceanAdventure.exe

Note: The compile command assumes that the SFML headers and libraries are located in C:\SFML. Your local configuration may require different paths or additional compiler settings.

🎯 Objective

Navigate through all five levels, avoid rocks and reefs, collect fuel and treasure, manage the ship's health and fuel, and reach the final destination to win the game.
