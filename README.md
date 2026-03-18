# A TEXT GAME?
(I asked AI to generate this README.md, and I'm not sure if it's correct! XD)

This project is a simple interactive C++ command-line application that simulates a game character. It allows you to initialize the character's basic stats (health, mana, and attack power) and interact with it by issuing commands such as healing, taking damage, and casting spells through standard input.

## Project Structure

The project is structured into basic header and source files:

- `include/character.h`: Class declaration for the `character` entity, highlighting its properties and method signatures.
- `src/Source.cpp`: Class implementation containing the definitions of the character's behaviors and stats management.
- `main.cpp`: The main entry point, handling the interactive console loop for character commands.

## Getting Started

### Prerequisites

A standard C++ compiler (like GCC, Clang, or MSVC) is required to build the project.

### Compilation

From the project root directory, you can compile the application using `g++` by including the headers and source files:

```bash
g++ -I./include main.cpp src/Source.cpp -o finalgame
```

### Running
run!

## Available Commands

When running the application, you can interact with your character using the following commands. The program continuously listens for commands until instructed to exit.

- `set <hp> <mp> <atk>`
  - **Description:** Sets the character's Health Points (HP), Mana Points (MP), and Attack Power (ATK).
  - **Example:** `set 100 50 20`

- `info`
  - **Description:** Prints the character's current HP, MP, and ATK to the console.
  - **Example:** `info`

- `heal <amount>`
  - **Description:** Increases the character's HP by the specified amount and prints the updated HP. Can be used to revive the character.
  - **Example:** `heal 20`

- `recover <amount>`
  - **Description:** Increases the character's MP by the specified amount. It will fail and print "Character is dead." if the character's HP is currently 0 or below.
  - **Example:** `recover 10`

- `hurt <amount>`
  - **Description:** Deals damage to the character, decreasing HP by the assigned amount. If the character's HP drops to 0 or below as a result, or if they are already dead, it triggers a "Character is dead." message. Otherwise, it prints the remaining HP.
  - **Example:** `hurt 15`

- `attack`
  - **Description:** Evaluates a standard attack. Returns the character's current attack power. Fails and prints a message if the character is dead.
  - **Example:** `attack`

- `cast <mp_amount>`
  - **Description:** Spends the specified amount of MP to perform a spell cast. Prints the remaining MP and evaluates magic potential based on half of the *remaining* MP. Fails if the character is dead or if they do not have enough MP to satisfy the cost.
  - **Example:** `cast 25`

- `exit`
  - **Description:** Exits the application and terminates the interactive loop.
  - **Example:** `exit`

## Class Structure (`character.h`)

### `character`
The core component of this project representing a game character unit.

#### Attributes:
- **`hp` (int):** Health Points.
- **`mp` (int):** Mana Points.
- **`atk` (int):** Attack Power.

#### Key Behaviors:
- **Stat Management:** Uses secure setters (`setHP()`, `setMP()`, `setATK()`) to ensure stats do not dive below 0. 
- **Verifications:** Subroutines like `hasHP()` and `hasMP()` dynamically verify the character's status before taking actions.
- **Interactions:** Methods (`heal()`, `recover()`, `hurt()`, `attack()`, `cast()`) execute basic RPG mechanics and relay status outcomes iteratively to standard output.