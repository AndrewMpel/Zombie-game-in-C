# Zombicide: Terminal Edition

## About The Project
This project is a custom C-based terminal game built as a variation of the popular board game "Zombicide". The ultimate goal of the game is to clear the board of all zombies, progressing through increasingly difficult levels until the outbreak is entirely eradicated. 

**Development Challenge:** To make this project significantly more challenging and to sharpen my raw programming skills, I developed the entire codebase exclusively using the `micro` text editor directly in the terminal. No modern IDEs, no Graphical User Interfaces (GUIs), and no mouse-driven debugging—just pure terminal environment coding.

---

## Core Gameplay Mechanics

* **The City (Board):** The game is played on a dynamically allocated N x M grid that represents a city. 
* **Entities:** The board is populated by randomly generated, indestructible contiguous buildings (represented by `#`) and up to 9 different types of zombies (represented by the numbers `1` through `9`). Empty street spaces are denoted by a `.`.
* **Level Progression:** When a player successfully eliminates all zombies on the board, they automatically advance to the next level. With each new level, the city map expands by 1 row and 1 column, and new random buildings and zombies are generated.
* **The Sound Source (Gravity):** Every level features a random "sound source" located on one of the four edges of the map (Top, Bottom, Left, or Right). Because zombies are attracted to noise, whenever zombies are killed, the remaining horde will "slide" toward the sound source to fill the newly emptied spaces.

---

## The Arsenal
The player has access to three highly specialized weapons to clear the streets:

* **Neurogun (`n` / `N` + coordinates):** A surgical weapon that targets a specific zombie's neural pathways. When fired, it recursively kills the targeted zombie and all connected zombies of the *exact same type*. 
* **Bomb (`b` / `B` + coordinates):** Heavy explosive ordnance. Dropping a bomb instantly kills any zombie at the target coordinate as well as all zombies in the 8 surrounding adjacent and diagonal spaces.
* **Plasma Gun (`p` / `P` + side + row/col):** Fires a devastating, straight-line energy beam across an entire row or column. It kills all zombies in its path regardless of type, but the beam is stopped instantly if it hits a building or the opposite edge of the board.

---

## Scoring System
The scoring system rewards strategic gameplay. Points are not awarded linearly. Instead, the game calculates score bonuses based on the size of the horde wiped out in a single attack and scales with the player's current level progression. 

---

## Setup & Compilation
*(Note: As this was built entirely via the terminal, it is designed to be compiled and run seamlessly in a standard Linux/Unix terminal environment)*

```bash
# Compile the game
gcc main.c -o zombicide

# Run the game
./zombicide
