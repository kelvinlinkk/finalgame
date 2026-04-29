# ⚔️ Text RPG — C++ CLI Turn-Based Battle Game

(I asked AI to generate this README.md, and I'm not sure if it's correct! XD)
A command-line turn-based RPG battle game written in C++. Players create a three-member party (Warrior, Fighter, Mage) and engage in round-by-round combat against an enemy using text commands — featuring healing, attacking, spellcasting, and other core RPG mechanics.

---

## 📁 Project Structure

```
finalgame/
├── main.cpp              # Entry point: create party & launch game
├── run.bat               # Windows one-click compile & run script
├── run.sh                # Linux / macOS one-click compile & run script
├── include/              # Header files (class declarations)
│   ├── character.h       #   Character class declaration
│   ├── weapon.h          #   Weapon class declaration
│   ├── party.h           #   Party class declaration
│   └── gamemanager.h     #   gameManager class declaration
├── src/                  # Source files (class implementations)
│   ├── character.cpp     #   Character class implementation
│   ├── weapon.cpp        #   Weapon class implementation
│   ├── party.cpp         #   Party class implementation
│   └── gamesystem.cpp    #   gameManager implementation + command parsing
├── test/                 # Unit tests
│   ├── basictest.cpp     #   Character basic functionality tests
│   ├── partytest.cpp     #   Party creation & operation tests
│   └── runtest.bat       #   Test compile & run script
├── bin/                  # Build output (executables)
│   ├── mygame.exe        #   Main game executable
│   └── basictest.exe     #   Test executable
└── .gitignore
```

---

## 🏗️ Architecture Overview

The project follows an **Object-Oriented Design (OOP)** approach, built around four core classes:

```
┌──────────────────────────────────────────────────────┐
│                    main.cpp                          │
│  ┌────────────────────────────────────────────────┐  │
│  │              gameManager                       │  │
│  │  ┌──────────────────┐  ┌──────────────────┐    │  |
│  │  │     Party        │  │  enemy: Character│    │  |
│  │  │  ┌────────────┐  │  │  (Slime)         │    │  |
│  │  │  │  warrior   │  │  └──────────────────┘    │  |
│  │  │  │  fighter   │  │                          │  │
│  │  │  │  mage      │  │                          │  │
│  │  │  └────────────┘  │                          │  │
│  │  └──────────────────┘                          │  │
│  └────────────────────────────────────────────────┘  │
└──────────────────────────────────────────────────────┘
```

### Class Dependency Graph

```
Weapon ◄─── Character ◄─── Party ◄─── gameManager
                 ▲                         │
                 └─── enemy ◄──────────────┘
```

---

## 📦 Class Reference

### 1. `Weapon`

**Files:** `include/weapon.h` · `src/weapon.cpp`

The lightest class, encapsulating basic weapon information.

| Member | Type | Description |
|--------|------|-------------|
| `name` | `std::string` (private) | Weapon name |
| `Weapon(std::string)` | Constructor | Initialize with a name |
| `getName()` | `std::string` | Returns the weapon name |

---

### 2. `Character`

**Files:** `include/character.h` · `src/character.cpp`

The core entity representing every character in the game — both party members and enemies.

#### Attributes (Private)

| Attribute | Type | Description |
|-----------|------|-------------|
| `name` | `std::string` | Character name |
| `hp` | `int` | Health Points |
| `mp` | `int` | Mana Points |
| `atk` | `int` | Attack Power |
| `weapon` | `std::unique_ptr<Weapon>` | Equipped weapon (exclusive ownership) |

#### Methods

| Method | Returns | Description |
|--------|---------|-------------|
| `Character()` | — | Default constructor: `name="untitiled"`, `hp=100`, `mp=100`, `atk=0` |
| `Character(name, hp, mp, atk, weaponName)` | — | Parameterized constructor, also creates a `Weapon` |
| `getINFO()` | `void` | Prints full status (name, HP, MP, ATK, weapon); shows death message if dead |
| `setINFO(name, hp, mp, atk)` | `void` | Batch-set character info |
| `hasHP()` / `hasMP()` | `bool` | Check whether HP / MP > 0 |
| `heal(amount)` | `void` | Restore HP (can revive a dead character) |
| `recover(amount)` | `void` | Restore MP (fails if character is dead) |
| `hurt(amount)` | `void` | Reduce HP; triggers death message when HP reaches 0 |
| `attack()` | `int` | Perform a physical attack; returns ATK and prints weapon name |
| `cast(mpCost)` | `int` | Spend MP to cast a spell; returns `remainingMP × 0.5` as damage |

#### Value Protection

- `setHP()` / `setMP()` use ternary operators to clamp values above 0:
  ```cpp
  this->hp = (hp < 0) ? 0 : hp;
  ```
- All combat methods (`recover`, `hurt`, `attack`, `cast`) check `hasHP()` before executing.

---

### 3. `Party`

**Files:** `include/party.h` · `src/party.cpp`

A container class managing the three party members and providing batch-operation interfaces.

#### Attributes

| Attribute | Type | Description |
|-----------|------|-------------|
| `partyname` | `std::string` (private) | Party name |
| `warrior` | `std::shared_ptr<Character>` (private) | Warrior (HP:100, MP:50, ATK:20, weapon: sword) |
| `fighter` | `std::shared_ptr<Character>` (private) | Fighter (HP:150, MP:20, ATK:30, weapon: axe) |
| `mage` | `std::shared_ptr<Character>` (private) | Mage (HP:70, MP:100, ATK:10, weapon: staff) |
| `isAlive` | `bool` (public) | Whether the party is still alive (determined by warrior's HP) |

#### Default Character Stats

| Role | HP | MP | ATK | Weapon |
|------|-----|-----|------|--------|
| Warrior | 100 | 50 | 20 | sword |
| Fighter | 150 | 20 | 30 | axe |
| Mage | 70 | 100 | 10 | staff |

#### Methods

All `party*` methods accept a character name to target a specific member, or `"all"` to apply to the entire party:

| Method | Description |
|--------|-------------|
| `getINFO()` | Print party name and all members' status |
| `partyHeal(name, amount)` | Restore HP for a specific character or the whole party |
| `partyHurt(name, amount)` | Deal damage to a specific character or the whole party |
| `partyRecover(name, amount)` | Restore MP for a specific character or the whole party |
| `partyCast(name, mpCost)` | Cast a spell with a specific character or the whole party; returns total damage |
| `partyAttack()` | All living members perform a physical attack; returns total damage |

---

### 4. `gameManager`

**Files:** `include/gamemanager.h` · `src/gamesystem.cpp`

The top-level controller orchestrating the entire game flow, including the command parser and turn-based logic.

#### Attributes

| Attribute | Type | Description |
|-----------|------|-------------|
| `playerparty` | `Party` (private) | The player's party |
| `enemy` | `std::shared_ptr<Character>` (private) | Enemy character (default: Slime, HP:120, MP:10, ATK:40) |
| `isGameover` | `bool` (private) | Whether the game has ended |

#### Command Parsing System

Uses `enum class Commands` paired with `std::map<std::string, Commands>` for string-to-command mapping:

```cpp
enum class Commands { set, info, heal, recover, hurt, cast, attack, unknown };

static std::map<std::string, Commands> commandMap{
    {"set", Commands::set},      {"info", Commands::info},
    {"heal", Commands::heal},    {"recover", Commands::recover},
    {"hurt", Commands::hurt},    {"cast", Commands::cast},
    {"attack", Commands::attack}
};
```

**Input parsing pipeline:**
1. Split user input with `std::stringstream`
2. First token → command name; remaining tokens → `std::vector<std::string>` arguments
3. Look up the corresponding `Commands` enum via `commandMap`
4. Dispatch execution with `switch-case`
5. Catch insufficient arguments with `try-catch (std::out_of_range)`

---

## 🎮 Game Flow

```
                     ┌──────────────────┐
                     │  Program Start   │
                     │    (main.cpp)    │
                     └───────┬──────────┘
                             │
                     ┌───────▼──────────┐
                     │  Enter party &   │
                     │  character names │
                     │  (4 names)       │
                     └───────┬──────────┘
                             │
                     ┌───────▼──────────┐
                     │  Create          │
                     │  gameManager     │
                     │  (auto-spawns    │
                     │   enemy: Slime)  │
                     └───────┬──────────┘
                             │
                     ┌───────▼──────────┐
                     │   startGame()    │
                     └───────┬──────────┘
                             │
              ┌──────────────▼───────────────┐
              │    Round Loop                │
              │                              │
              │  1. Display round number     │
              │  2. Show enemy & party stats │
              │  3. Player turn (playerTurn) │
              │     └─ Input command → exec  │
              │  4. Check enemy dead → WIN   │
              │  5. Enemy attacks all party  │
              │  6. Check party dead → LOSE  │
              │  7. Round++ → continue loop  │
              │                              │
              └──────────────────────────────┘
                             │
              ┌──────────────▼──────────────┐
              │         Game Over           │
              │  "You beat the Enemy!" or   │
              │  "You have been defeated!"  │
              └─────────────────────────────┘
```

---

## 🕹️ Command Reference

During the player's turn, enter a command to take action. Each command ends the current turn.

| Command | Format | Description | Example |
|---------|--------|-------------|---------|
| **info** | `info` | Display all party members' status | `info` |
| **heal** | `heal <name/all> <amount>` | Restore HP for a character or the whole party | `heal Arthur 30` |
| **recover** | `recover <name/all> <amount>` | Restore MP for a character or the whole party | `recover all 20` |
| **hurt** | `hurt <name/all> <amount>` | Deal damage to a character or the whole party | `hurt Mage 10` |
| **cast** | `cast <name/all> <mpCost>` | Spend MP to cast a spell | `cast Gandalf 25` |
| **attack** | `attack` | All living party members perform a physical attack | `attack` |

> **Note:** Character names are case-sensitive and must exactly match the names entered during party creation.

---

## 🛠️ Implementation Details & Design Decisions

### Memory Management

The project uses **C++ smart pointers** for memory management, avoiding manual `new` / `delete` and potential memory leaks:

| Smart Pointer | Usage | Rationale |
|---------------|-------|-----------|
| `std::unique_ptr<Weapon>` | `Character` owns a `Weapon` | A weapon belongs exclusively to one character; no sharing needed |
| `std::shared_ptr<Character>` | `Party` holds members / `gameManager` holds `enemy` | Characters may be referenced from multiple places (party operations, game manager) |

### Object-Oriented Design Principles

- **Encapsulation:** All data members are `private`, accessed through getters/setters. Setters include value clamping logic to maintain invariants.
- **Composition:** `Character` has-a `Weapon`; `Party` has-a set of `Character`s; `gameManager` has-a `Party` + `Character` (enemy) — forming a clear hierarchical ownership model.
- **Separation of Concerns:** Game flow logic (`gameManager`), character behavior (`Character`), and party management (`Party`) are cleanly separated into distinct classes.

### Command System Design

Follows a **Strategy-like pattern:**
1. `std::map` maps strings to enum values, avoiding lengthy `if-else` chains
2. `std::stringstream` provides flexible input tokenization
3. `switch-case` dispatches to the appropriate handler
4. `try-catch` gracefully handles missing arguments

### Turn-Based Combat Design

- The player executes **one command per turn**, after which the enemy automatically takes its turn
- The enemy uses `attack()` to deal equal damage to all party members
- **Win condition:** Enemy HP drops to 0
- **Lose condition:** Party `isAlive` becomes `false` (determined by the warrior's HP)

---

## 🚀 Build & Run

### Prerequisites

- C++ compiler (C++14 or later): GCC, Clang, or MSVC

### Quick Start

**Windows:**
```cmd
.\run.bat
```

**Linux / macOS:**
```bash
chmod +x run.sh
./run.sh
```

### Manual Compilation

```bash
g++ -o bin/mygame -g src/*.cpp -I include ./main.cpp
```

Run:
```bash
# Linux / macOS
./bin/mygame

# Windows
.\bin\mygame.exe
```

### Running Tests

```cmd
cd test
.\runtest.bat
```

---

## 📝 Gameplay Example

```
Create your party:
MyTeam Arthur Lancelot Gandalf

Fight start!

Round 1
-Character:Slime
--HP:120
--MP:10
--ATK:40
--Weapon:sticky ball
Party name:MyTeam
-Character:Arthur
--HP:100
--MP:50
--ATK:20
--Weapon:sword
-Character:Lancelot
--HP:150
--MP:20
--ATK:30
--Weapon:axe
-Character:Gandalf
--HP:70
--MP:100
--ATK:10
--Weapon:staff
Input your action:
attack
-Arthur attacks with sword! ATK:20
-Lancelot attacks with axe! ATK:30
-Gandalf attacks with staff! ATK:10
-Slime HP:60
-Slime attacks with sticky ball! ATK:40
-Arthur HP:60
-Lancelot HP:110
-Gandalf HP:30
```

---

## 📄 License

No license specified.