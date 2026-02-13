# Domino

A command-line Domino game implemented in C++ with an MVC architecture, developed as an academic project at PUC. Supports Player vs. Player and Player vs. AI modes, with full game logic, automatic scoring, and save/load functionality.

---

## Features

- Player vs. Player and Player vs. AI game modes
- Complete rule enforcement: shuffling, dealing, playing pieces, drawing from the boneyard, and passing turns
- Automatic win detection when a player empties their hand or the game reaches a blocked state
- Save and load game state via `domino.dat`
- In-program display of the game rules

---

## Architecture

The project follows the Model-View-Controller (MVC) pattern:

**Model** (`DOM-KLRR-MODEL.h` / `.cpp`) — Defines the core data structures: domino pieces (`Peca`) and the game table (`Mesa`). Responsible for generating the standard set of 28 pieces.

**View** (`DOM-KLRR-VIEW.h` / `.cpp`) — Handles all terminal output, including the main menu, in-game menus, table state rendering, and rules display.

**Controller** (`DOM-KLRR-CONTROLLER.h` / `.cpp`) — Orchestrates game flow, processes user input, enforces rules, manages turns, and controls AI behavior.

**Entry Point** (`DOM-KLRR-MAIN.cpp`) — Initializes the game objects and starts the main loop.

**Persistence** (`domino.dat`) — Binary file used to save and restore game state.

---

## Platform Note

The code uses `<windows.h>` for `Sleep()` and `system("cls")`, making it Windows-native out of the box. To build on Linux or macOS, replace:

- `Sleep(ms)` with `usleep(ms * 1000)` from `<unistd.h>`
- `system("cls")` with `system("clear")`

---

## Building

```bash
g++ DOM-KLRR-MAIN.cpp DOM-KLRR-MODEL.cpp DOM-KLRR-VIEW.cpp DOM-KLRR-CONTROLLER.cpp -o domino
```

---

## Running

```bash
./domino
```

---

## Main Menu

| Option | Action |
|--------|--------|
| `1` | Start a new 2-player game |
| `2` | Start a game against the AI |
| `3` | Return to the current interrupted game |
| `4` | Display the rules |
| `5` | Save the current game to `domino.dat` |
| `6` | Load a saved game from `domino.dat` |
| `0` | Exit the program |

## In-Game Controls

| Key | Action |
|-----|--------|
| `J` | Play a piece from your hand |
| `C` | Draw a piece from the boneyard |
| `P` | Pass your turn (only when boneyard is empty and no valid moves exist) |
| `S` | Return to the main menu |

---

## Authors

Developed by the KLRR group as part of the curriculum at PUC:

- Kaua Bezerra Brito
- Liam Vedovato Lopes
- Raul Kolaric
- Rodrigo Ward Leite
