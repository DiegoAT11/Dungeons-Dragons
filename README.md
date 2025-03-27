# Dungeons & Dragons Game

Welcome to the **Dungeons & Dragons Game** project! This project simulates the Dungeons & Dragons gameplay mechanics using various data structures, such as **Linked Lists**, **Stacks**, **Queues**, **Binary Search Trees (AVL)**, and other components that represent **monsters**, **spells**, **players**, and more.

## General Description

The game uses several classes to represent various game entities such as **Monsters**, **Players**, **Spells**, and **Dungeons**. Each **monster** has attributes like **strength**, **health**, and **special abilities**, while the **player** has attributes such as **name**, **race**, **health points (HP)**, and **level points (LP)**. The goal is to create an immersive Dungeons & Dragons experience where players face dynamic and unpredictable challenges.

## Paradigm
Object-oriented programming (OOP), with a focus on abstraction and code reuse.

## Project Objectives
1. Create a dynamic monster system that allows players to face different creatures in each game.
2. Optimize creature handling using linked lists to improve performance in memory management and data access.
 
## Data Structures and Classes

### Linked List (`list.h`)

The **Linked List** is a key component in this game, used to store various types of game entities such as **Monsters**, **Spells**, and more.


### AVL Tree (`AVL.h`)

The **AVL Tree** is used to maintain a balanced binary search tree for efficient searching, inserting, and deleting elements. It is especially useful for managing **Monsters**.

### Monster (`monster.h`)

The **Monster** class is designed to represent different types of monsters in the game. Each monster has attributes such as name, challenge rating (CR), and health points (HP).

### Player (`player.h`)

The **Player** class represents the player character in the game, with attributes like name, race, health points (HP), and level points (LP).

### Dungeon (`mazmorra.h`)

The **Dungeon** class represents the dungeon where the players face monsters and challenges. The sorting method organizes the dungeon’s content.

### Spell (`spell.h`)

The **Spell** class represents magical abilities in the game, with attributes such as spell type, name, and dice values.

### Game (`game.h`)

The **Game** class coordinates the entire game, interacting with multiple instances of the **LinkedList** class to manage **Monsters**, **Spells**, and **Dungeon**.

