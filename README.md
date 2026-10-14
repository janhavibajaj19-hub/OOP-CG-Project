# Ocean Adventure

Ocean Adventure is a 2D ocean survival game developed in C++ using SFML 2.6.1. The player controls a ship, navigates through a dynamic ocean, avoids hazards, manages health and fuel, collects treasure, and reaches the destination to complete the voyage.

## Overview

This project was developed as a mini-project for Object-Oriented Programming and Computer Graphics. It combines gameplay mechanics, collision detection, environmental effects, and 2D graphics in an interactive game.

## Features

- Ship movement and navigation using arrow keys
- Animated ocean background
- Weather and current effects
- Obstacles such as rocks and reefs
- Health and fuel management
- Fuel and treasure collection
- Score tracking
- Easy, Medium, and Hard difficulty levels
- Destination-based objective
- Win and lose conditions
- Restart after victory or defeat

## Gameplay

The player must survive the voyage by:

- Steering the ship safely through the ocean
- Avoiding rocks and reefs
- Managing health and fuel
- Collecting fuel to continue the journey
- Collecting treasure to earn bonus points
- Reaching the destination successfully

## Controls

| Key | Action |
|---|---|
| Arrow Keys | Move the ship |
| Mouse | Navigate menus and select options |
| Escape | Return to the main menu from supported screens |
| R | Restart after victory or defeat |

## Scoring System

| Action | Points |
|---|---:|
| Collect a treasure chest | +50 |
| Reach the destination | +100 |
| Finish with health above 50 | +25 bonus |
| Finish with fuel above 25 | +25 bonus |

Fuel barrels restore fuel but do not add points.

## Survival Rules

- Rocks cause damage to the ship.
- Reefs cause damage to the ship.
- Fuel decreases while the ship is moving.
- Weather currents can push the ship.
- The difficulty level affects fuel consumption and obstacle damage.
- The game ends when the ship runs out of health or fuel.
- Reaching the destination triggers the victory screen.

## Technologies Used

- **Language:** C++
- **Graphics Library:** SFML 2.6.1
- **Compiler:** MinGW-w64 (G++)
- **Development Environment:** Visual Studio Code
- **Version Control:** Git
- **Repository Hosting:** GitHub

## Object-Oriented Programming

The project uses the following OOP concepts:

- **Encapsulation:** Managing data such as health, fuel, and score through class members and functions.
- **Inheritance:** Using base classes to share functionality between related game objects.
- **Polymorphism:** Using virtual functions to support different implementations through a common interface.
- **Abstraction:** Defining common functionality through the `GameObject` base class.

## Computer Graphics Concepts

- 2D shape rendering
- Coordinate systems and object positioning
- Translation, scaling, and rotation
- Animated waves and water effects
- Real-time rendering
- Bounding-box collision detection
- Heads-Up Display (HUD)

## Project Structure

The project is organised into a main source file and separate header files for the game systems.

| File | Purpose |
|---|---|
| `main.cpp` | Starts the game |
| `Game.h` | Manages game states, input, updates, rendering, and gameplay |
| `GameObject.h` | Base class for game objects |
| `Ship.h` | Handles ship movement, health, fuel, and score |
| `Obstacle.h` | Defines rocks, reefs, and obstacle damage |
| `Resource.h` | Handles fuel and treasure collection |
| `Destination.h` | Defines and draws the destination |
| `Weather.h` | Manages weather conditions and currents |

## Requirements

- A compatible C++ compiler
- SFML 2.6.1
- MinGW-w64 or another compatible compiler toolchain
- Windows environment for the example command below

## Build and Run

Make sure SFML is installed and configured on your system.

Open a terminal in the project directory and compile the project using MinGW:

```bash
g++ main.cpp -o OceanAdventure.exe -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system
```

Adjust the include and library paths if SFML is installed in a different location.

Run the generated executable in PowerShell:

```powershell
.\OceanAdventure.exe
```

Ensure the required SFML runtime DLL files are available when running the game.

## Future Improvements

- Sound effects and background music
- More detailed ship and ocean animations
- Improved visual effects for different weather conditions
- Additional obstacles and collectible resources
- A high-score system

## Academic Context

**Course:** Object-Oriented Programming and Computer Graphics  
**Academic Year:** SY Computer Engineering  
**Project Type:** Mini-Project
