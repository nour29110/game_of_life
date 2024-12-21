# Game of Life Implementation

This repository contains a C++ implementation of **Conway's Game of Life**, a cellular automaton devised by British mathematician John Horton Conway in 1970. This program simulates a grid-based system where cells evolve over generations based on a set of rules inspired by life and death. 

## Table of Contents
1. [About the Project](#about-the-project)
2. [Features](#features)
3. [How It Works](#how-it-works)
4. [Usage](#usage)
5. [Dependencies](#dependencies)
6. [How to Run](#how-to-run)

---

## About the Project

Conway's Game of Life is a zero-player game where the evolution of the system is determined solely by its initial state. This program provides multiple ways to initialize the grid (e.g., random generation, file input, or manual user input) and visualize the evolution of the cells. It is designed to simulate the rules of life in a two-dimensional grid.

### Purpose
This project is a hands-on demonstration of computational simulation, object management, and interactive visualization, all implemented in C++. It serves as an educational resource for understanding:
- Cellular automata.
- Memory management in C++.
- File handling and user interaction in console applications.

---

## Features

1. **Grid Initialization:**
   - Randomized starting grid.
   - Grid from a user-specified file.
   - Manual input for custom grids.

2. **Rules of Evolution:**
   - A cell with two or three live neighbors survives.
   - A dead cell with exactly three live neighbors becomes alive.
   - All other cells die or remain dead.

3. **Interactive Modes:**
   - Continuous mode (`R`): The simulation runs continuously without pause.
   - Step-by-step mode (`S`): The simulation pauses after each generation.

4. **Reset Mechanism:**
   - After a fixed number of cycles, the grid resets to avoid stagnation.

5. **Save and Load Functionality:**
   - Save a grid to a file for later use.
   - Load a grid from a file.

---

## How It Works

The simulation is based on a 2D grid where each cell can either be alive (`X`) or dead (` `). The evolution of the grid follows these rules:
- A live cell with fewer than 2 live neighbors dies (underpopulation).
- A live cell with more than 3 live neighbors dies (overpopulation).
- A live cell with 2 or 3 live neighbors survives.
- A dead cell with exactly 3 live neighbors becomes alive (reproduction).

The program implements:
- Random initialization for generating a starting grid.
- File I/O to save/load grids.
- Dynamic memory allocation to manage grid sizes efficiently.

---

## Usage

### Main Menu
1. **Read grid from file**: Load a pre-defined grid stored in a file.
2. **Use default grid**: Generate a random grid based on preset probabilities.
3. **Input grid manually**: Input a custom grid configuration line by line.

### Simulation Modes
- Continuous simulation (`SWITCH = 'R'`): Runs until interrupted.
- Step-by-step simulation (`SWITCH = 'S'`): Pauses after each generation.

---

## Dependencies

- C++ Standard Library (`iostream`, `fstream`, `cstdlib`, `unistd.h`, `ctime`, etc.).
- Compatible with Unix-based systems (uses `system("clear")` for console clearing).

---

## How to Run

1. **Compile the Code**:
   Use the following command to compile the program:
   ```bash
   g++ -o game_of_life game_of_life.cpp
   ./game_of_life
   
