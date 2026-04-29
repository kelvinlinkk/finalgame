# A TEXT GAME?

(I asked AI to generate this README.md, and I'm not sure if it's correct! XD)

This project is a simple interactive C++ command-line application that simulates a game character. It allows you to initialize the character's basic stats (health, mana, and attack power) and interact with it by issuing commands such as healing, taking damage, and casting spells through standard input.

## Project Structure

The project is structured into basic header and source files:

- `include/character.h`: Class declaration for the `character` entity, highlighting its properties and method signatures.
- `include/command.h`: Header file that defines the `gamemanager` namespace and command handling function.
- `src/character.cpp`: Class implementation containing the definitions of the character's behaviors and stats management.
- `src/command.cpp`: Implementation of command parsing using `std::stringstream` and mapped enumeration (`std::map<std::string, Commands>`).
- `main.cpp`: The main entry point, initializing the character dynamically (`new character()`) and running the interactive console loop.
- `run.bat` & `run.sh`: Helper scripts for quick compilation and execution on Windows and Linux/macOS.

## Getting Started

### Prerequisites

A standard C++ compiler (like GCC, Clang, or MSVC) is required to build the project.

### Compilation & Running

We provide convenient scripts to compile and immediately run the program. The executable is placed in the `bin/` directory.

**On Windows:**

```cmd
.\run.bat
```

**On Linux / macOS:**

```bash
./run.sh
```

**Manual Compilation:**

If you prefer compiling manually, run:

```bash
g++ -o bin/mygame -g src/*.cpp -I include ./main.cpp
```

Then execute it via `./bin/mygame` (or `.\bin\mygame.exe` on Windows).

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

## Code Implementation Details & Class Structure

### `character` (`character.h` & `character.cpp`)

The core component of this project representing a game character unit.

**Attributes:**

- `hp` (int): Health Points.
- `mp` (int): Mana Points.
- `atk` (int): Attack Power.

**Key Behaviors:**

- **Stat Management:** Uses secure setters (`setHP()`, `setMP()`, `setATK()`) to ensure stats (like HP/MP) do not drop below 0.
- **Verifications:** Subroutines like `hasHP()` and `hasMP()` dynamically verify the character's status before taking actions. Actions such as `cast()` or `recover()` will fail if `!hasHP()` (Character is dead).
- **Interactions:** Methods (`heal()`, `recover()`, `hurt()`, `attack()`, `cast()`) execute basic RPG mechanics. Note that the destructor `~character()` prints a message on cleanup.

### `gamemanager` (`command.h` & `command.cpp`)

- **Command Architecture:** Employs an `enum class Commands` for clear operations mapping.
- **Input Parsing:** Unifies string parsing in `handlingCommand()` via `std::stringstream` to extract variable arguments (`std::vector<int> args`) and securely maps textual inputs to actual enum events using `std::map<std::string, Commands> commandMap`.
- **Exception Handling:** A try-catch block (`std::out_of_range& e`) gracefully handles command arguments that are out of bounds. Unrecognized actions trigger an "Invalid input." fallback.

### `main.cpp` Initialization & Loop

- **Memory Management:** Dynamically allocates memory for the character (`new character()`) and cleans it up using `delete c;` to avoid memory leaks.
- **Game Loop:** A clean `do-while` loop processes user input line by line with `std::getline()`. The loop continues until `gamemanager::handlingCommand()` returns `false` (when receiving the `exit` command).