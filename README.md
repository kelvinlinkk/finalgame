# ⚔️ Text RPG — C++ CLI Turn-Based Battle Game

A command-line turn-based RPG battle game written in C++. Players create a three-member party (Hero, Warrior, Mage) and engage in round-by-round combat against a monster — featuring healing, attacking, spellcasting, weapon upgrading, and other core RPG mechanics.

---

## 📁 Project Structure

```
finalgame/
├── main.cpp              # Entry point: create party & launch game
├── run.bat               # Windows one-click compile & run script
├── run.sh                # Linux / macOS one-click compile & run script
├── include/              # Header files (class declarations)
│   ├── character.h       #   Character base class + Hero / Warrior / Mage / Monster
│   ├── weapon.h          #   Weapon class declaration
│   ├── party.h           #   Party class declaration
│   └── gamemanager.h     #   gameManager class declaration
├── src/                  # Source files (class implementations)
│   ├── character.cpp     #   Character + subclass implementations
│   ├── weapon.cpp        #   Weapon class implementation
│   ├── party.cpp         #   Party class implementation
│   └── gamemanager.cpp   #   gameManager implementation + command parsing
├── test/                 # Unit tests
│   ├── basictest.cpp     #   Character basic functionality tests
│   ├── partytest.cpp     #   Party creation & operation tests
│   └── runtest.bat       #   Test compile & run script (Windows)
├── bin/                  # Build output (executables)
└── .gitignore
```

---

## 🏗️ Architecture Overview

The project follows an **Object-Oriented Design (OOP)** approach with **inheritance** and **polymorphism**, built around an abstract `Character` base class and four core modules:

```
┌──────────────────────────────────────────────────────────┐
│                      main.cpp                            │
│  ┌────────────────────────────────────────────────────┐  │
│  │                gameManager                         │  │
│  │  ┌──────────────────────┐  ┌────────────────────┐  │  │
│  │  │       Party          │  │  enemy: Monster    │  │  │
│  │  │  ┌──────────────-┐   │  │  (Slime)           │  │  │
│  │  │  │  hero: Hero   │   │  └────────────────────┘  │  │
│  │  │  │  warrior: War │   │                          │  │
│  │  │  │  mage: Mage   │   │                          │  │
│  │  │  └──────────────-┘   │                          │  │
│  │  └──────────────────────┘                          │  │
│  └────────────────────────────────────────────────────┘  │
└──────────────────────────────────────────────────────────┘
```

### Class Inheritance Hierarchy

```
                Character (abstract)
               /     |      \       \
           Hero   Warrior   Mage   Monster
```

### Class Dependency Graph

```
Weapon ◄─── Character (abstract) ◄─── Party ◄─── gameManager
                     ▲                               │
              Hero / Warrior /                       │
              Mage / Monster                         │
                     ▲                               │
                     └─── enemy (Monster) ◄──────────┘
```

---

## 📦 Class Reference

### 1. `Weapon`

**Files:** `include/weapon.h` · `src/weapon.cpp`

The lightest class, encapsulating weapon information with a level-up system.

| Member | Type | Description |
|--------|------|-------------|
| `name` | `std::string` (private) | Weapon name |
| `lvl` | `int` (private) | Weapon level (starts at 1) |
| `Weapon(std::string)` | Constructor | Initialize with a name, level defaults to 1 |
| `getName()` | `std::string` | Returns the weapon name |
| `getlvl()` | `int` | Returns the weapon level |
| `upgrade()` | `void` | Increases weapon level by 1 |

---

### 2. `Character` (Abstract Base Class)

**Files:** `include/character.h` · `src/character.cpp`

The abstract base class representing every character in the game. Cannot be instantiated directly — all characters must be one of its subclasses.

#### Attributes (Protected)

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
| `getINFO()` | `void` | Prints status (name, HP, ATK, weapon + level); shows death message if dead |
| `setINFO(name, hp, mp, atk)` | `void` | Batch-set character info |
| `hasHP()` / `hasMP()` | `bool` | Check whether HP / MP > 0 |
| `getName()` / `getHP()` / `getMP()` / `getATK()` | — | Getters |
| `setName()` / `setHP()` / `setMP()` / `setATK()` | — | Setters (HP & MP clamped ≥ 0) |
| `heal(amount)` | `void` | Restore HP (can revive a dead character) |
| `recover(amount)` | `void` | Restore MP (fails if character is dead) |
| `hurt(amount)` | `void` | Reduce HP; triggers death message when HP reaches 0 |
| `attack()` | `int` | Perform a physical attack; returns ATK and prints weapon name |
| `cast()` | `int` | Base implementation returns 0; overridden by subclasses |
| `action(target)` | `void` | **Pure virtual** — each subclass defines its own action menu |

#### Operator Overloads

| Operator | Description |
|----------|-------------|
| `operator<<` | Stream output: prints full character status |
| `operator++` (prefix) | Level up: HP +20, ATK +10, weapon upgrade |
| `operator+=` (unique_ptr\<Weapon\>) | Equip a new weapon (replaces old one) |

#### Value Protection

- `setHP()` / `setMP()` clamp values above 0:
  ```cpp
  this->hp = (hp < 0) ? 0 : hp;
  ```
- Combat methods (`recover`, `hurt`, `attack`) check `hasHP()` before executing.

---

### 3. Character Subclasses

Each subclass inherits from `Character` and overrides `cast()` and `action()`:

| Subclass | Skill Name | MP Cost | Effect | Damage |
|----------|------------|---------|--------|--------|
| **Hero** | Cheer | 10 MP | Self ATK +10 | 0 (buff) |
| **Warrior** | Taunt | 5 MP | Self HP +30 | 0 (buff) |
| **Mage** | Fireball | 20 MP | Deals fixed 60 damage to enemy | 60 |
| **Monster** | — | — | No special skill | — |

#### Individual Action Menus

During combat, each party member gets their own action prompt:

- **Hero**: `1. attack  2. cheer`
- **Warrior**: `1. attack  2. taunt`
- **Mage**: `1. attack  2. fireball`

---

### 4. `Party`

**Files:** `include/party.h` · `src/party.cpp`

A container class managing the three party members and providing batch-operation interfaces.

#### Attributes

| Attribute | Type | Description |
|-----------|------|-------------|
| `partyname` | `std::string` (private) | Party name |
| `hero` | `std::shared_ptr<Hero>` (private) | Hero (HP:100, MP:50, ATK:20, weapon: sword) |
| `warrior` | `std::shared_ptr<Warrior>` (private) | Warrior (HP:150, MP:20, ATK:30, weapon: axe) |
| `mage` | `std::shared_ptr<Mage>` (private) | Mage (HP:70, MP:100, ATK:10, weapon: staff) |
| `isAlive` | `bool` (public) | Whether any party member is still alive |

#### Default Character Stats

| Role | HP | MP | ATK | Weapon | Skill |
|------|-----|-----|------|--------|-------|
| Hero | 100 | 50 | 20 | sword | Cheer (ATK +10) |
| Warrior | 150 | 20 | 30 | axe | Taunt (HP +30) |
| Mage | 70 | 100 | 10 | staff | Fireball (60 dmg) |

#### Methods

Party commands accept a character name or `"all"` to target the entire party:

| Method | Description |
|--------|-------------|
| `getINFO()` | Print party name and all members' status |
| `partyHeal(name, amount)` | Restore HP for a specific character or the whole party |
| `partyHurt(name, amount)` | Deal damage to a specific character or the whole party |
| `partyRecover(name, amount)` | Restore MP for a specific character or the whole party |
| `partyCast(name)` | A specific character or all members cast their skill; returns total damage |
| `partyAttack()` | All living members perform a physical attack; returns total damage |
| `partyUpgrade(name)` | Level up a character or all (HP +20, ATK +10, weapon LV +1) |
| `partyEquip(name, weaponName)` | Equip a new weapon for a character or all members |
| `memberaction(enemy)` | Each living member takes their individual action against the enemy |

#### Alive Check

`isAlive` is `true` as long as **any** party member has HP > 0:
```cpp
isAlive = hero->hasHP() || warrior->hasHP() || mage->hasHP();
```

---

### 5. `gameManager`

**Files:** `include/gamemanager.h` · `src/gamemanager.cpp`

The top-level controller orchestrating the entire game flow, including the command parser and turn-based logic.

#### Attributes

| Attribute | Type | Description |
|-----------|------|-------------|
| `playerparty` | `Party` (private) | The player's party |
| `enemy` | `std::shared_ptr<Character>` (private) | Enemy (default: Slime, HP:120, MP:10, ATK:40, weapon: sticky ball) |
| `isGameover` | `bool` (private) | Whether the game has ended |

#### Command Parsing System

Uses `enum class Commands` paired with `std::map<std::string, Commands>` for string-to-command mapping:

```cpp
enum class Commands { set, info, heal, recover, hurt, cast, attack, upgrade, equip, unknown };

static std::map<std::string, Commands> commandMap{
    {"set", Commands::set},       {"info", Commands::info},
    {"heal", Commands::heal},     {"recover", Commands::recover},
    {"hurt", Commands::hurt},     {"cast", Commands::cast},
    {"attack", Commands::attack}, {"upgrade", Commands::upgrade},
    {"equip", Commands::equip}
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

The game features a **two-phase turn system**: a party command phase followed by individual member actions.

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
              │  3. Party command phase      │
              │     └─ heal / recover /      │
              │        cast / upgrade /      │
              │        equip / attack / info │
              │  4. Member action phase      │
              │     └─ Each living member    │
              │        chooses: attack or    │
              │        use skill             │
              │  5. Check enemy dead → WIN   │
              │  6. Enemy attacks all party  │
              │  7. Check party dead → LOSE  │
              │  8. Round++ → continue loop  │
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

### Phase 1: Party Commands

During the party command phase, enter commands to buff or manage your team. Most commands end the phase and move to individual actions.

| Command | Format | Description | Example |
|---------|--------|-------------|---------|
| **info** | `info` | Display all party members' status (does **not** end the phase) | `info` |
| **heal** | `heal <name/all> <amount>` | Restore HP for a character or the whole party | `heal Arthur 30` |
| **recover** | `recover <name/all> <amount>` | Restore MP for a character or the whole party | `recover all 20` |
| **hurt** | `hurt <name/all> <amount>` | Deal damage to a character or the whole party | `hurt all 10` |
| **cast** | `cast <name/all>` | Character(s) use their class skill | `cast Gandalf` |
| **attack** | `attack` | All living party members perform a physical attack on the enemy | `attack` |
| **upgrade** | `upgrade <name/all>` | Level up a character (HP +20, ATK +10, weapon LV +1) | `upgrade all` |
| **equip** | `equip <name> <weaponName>` | Equip a new weapon for a character | `equip Arthur excalibur` |

> **Note:** Character names are case-sensitive and must exactly match the names entered during party creation.

### Phase 2: Individual Member Actions

After the party command, each living party member takes their turn in order (Hero → Warrior → Mage). Each member gets a choice:

| Role | Option 1 | Option 2 |
|------|----------|----------|
| **Hero** | Attack (deal ATK damage) | Cheer (self ATK +10, costs 10 MP) |
| **Warrior** | Attack (deal ATK damage) | Taunt (self HP +30, costs 5 MP) |
| **Mage** | Attack (deal ATK damage) | Fireball (deal 60 damage, costs 20 MP) |

---

## 🛠️ Implementation Details & Design Decisions

### Memory Management

The project uses **C++ smart pointers** for memory management, avoiding manual `new` / `delete` and potential memory leaks:

| Smart Pointer | Usage | Rationale |
|---------------|-------|-----------| 
| `std::unique_ptr<Weapon>` | `Character` owns a `Weapon` | A weapon belongs exclusively to one character; no sharing needed |
| `std::shared_ptr<Character>` | `Party` holds members / `gameManager` holds `enemy` | Characters may be referenced from multiple places (party operations, game manager, action targets) |

### Object-Oriented Design Principles

- **Abstraction & Polymorphism:** `Character` is an abstract class with a pure virtual `action()` method. Each subclass (Hero, Warrior, Mage, Monster) provides its own implementation, enabling unique behavior per character type.
- **Inheritance:** `Hero`, `Warrior`, `Mage`, and `Monster` all derive from `Character`, sharing common attributes and operations while adding class-specific skills.
- **Encapsulation:** Data members are `protected` / `private`, accessed through getters/setters. Setters include value clamping logic to maintain invariants.
- **Composition:** `Character` has-a `Weapon`; `Party` has-a set of `Character` subclasses; `gameManager` has-a `Party` + `Monster` (enemy) — forming a clear hierarchical ownership model.
- **Operator Overloading:** `<<` for pretty-printing, `++` for leveling up, `+=` for weapon equipping — making the code expressive and idiomatic.
- **Separation of Concerns:** Game flow logic (`gameManager`), character behavior (`Character` hierarchy), party management (`Party`), and items (`Weapon`) are cleanly separated into distinct classes.

### Command System Design

Follows a **Strategy-like pattern:**
1. `std::map` maps strings to enum values, avoiding lengthy `if-else` chains
2. `std::stringstream` provides flexible input tokenization
3. `switch-case` dispatches to the appropriate handler
4. `try-catch` gracefully handles missing arguments

### Turn-Based Combat Design

- **Two-phase turn:** First, the player issues a party-level command (heal, cast, attack, etc.). Then, each living member individually chooses their action (attack or class skill).
- After all party actions, the enemy automatically attacks, dealing equal damage to **all** party members.
- **Win condition:** Enemy HP drops to 0
- **Lose condition:** All party members are dead (`isAlive = false`)

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
--HP: 120
--ATK: 40
--Weapon: sticky ball(LV.1)
Party name: MyTeam
-Character:Arthur
--HP: 100
--ATK: 20
--Weapon: sword(LV.1)
-Character:Lancelot
--HP: 150
--ATK: 30
--Weapon: axe(LV.1)
-Character:Gandalf
--HP: 70
--ATK: 10
--Weapon: staff(LV.1)
Input party action:
attack
-Arthur attacks with sword! ATK:20
-Lancelot attacks with axe! ATK:30
-Gandalf attacks with staff! ATK:10
-Slime HP:60

Arthur's action (1. attack 2. cheer):
1
-Arthur attacks with sword! ATK:20
-Slime HP:40

Lancelot's action (1. attack 2. taunt):
1
-Lancelot attacks with axe! ATK:30
-Slime HP:10

Gandalf's action (1. attack 2. fireball):
2
-Gandalf casts Fireball! Deals 60 damage. MP:80
-Slime is dead.
You beat the Enemy:Slime!
```

---

## 📄 License

No license specified.