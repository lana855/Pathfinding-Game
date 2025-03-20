# Pathfinding Game with Dijkstra's Algorithm in C++

This project is a text-based pathfinding game implemented in C++. The goal of the game is to find a valid path between a start point (`S`) and an end point (`E`) on a grid, avoiding randomly placed walls (`#`). The player inputs coordinates to navigate the grid, and if the path matches the hidden path computed using **Dijkstra's Algorithm**, a hidden achievement is unlocked.

## Key Features

- **Dijkstra's Algorithm**: The hidden path is computed using Dijkstra's algorithm.
- **Interactive Gameplay**: Users input coordinates (`x y`) to navigate through a grid, with consecutive points forming the path.
- **Random Grid Generation**: A random grid is generated with walls, a start point, and an end point.
- **Hidden Achievements**: Players who correctly find the hidden path are awarded an achievement in the form of heart-shaped ASCII art.
- **UTF-16 Encoding**: The game uses UTF-16 encoding to display special characters (e.g., hearts) in the console.

## How to Play

1. **Start the Game**: After entering your name, a random grid will be generated.
2. **Navigate the Grid**: You will be prompted to input `(x y)` coordinates step-by-step. Each point you enter will be checked to ensure it's valid (within the grid, not a wall, and consecutive to the last point).
3. **Reach the End**: When you reach the end point, the game checks if your path matches the shortest path found by Dijkstra’s algorithm.
4. **Unlock Hidden Achievement**: If your path is correct, a hidden achievement (a heart-shaped ASCII art) is displayed.

## Features and Functions

### `Grid(const vector<vector<int>>& grid)`
Displays the grid on the console, representing walls, paths, start (`S`), end (`E`), and the user’s path.

### `randomPt(int gridS, int quadrant)`
Generates a random point within a specified quadrant of the grid.

### `dijkstra(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end)`
Implements Dijkstra’s algorithm to find the hidden paths from the start point to the end point.

### `Hidden(const wstring& name)`
Displays a hidden achievement message with ASCII art when the user completes the path correctly.

### `main()`
This is the entry point where the grid is set up, the user interacts with the game, and the pathfinding process happens.

## Requirements

- **C++11** or later
- A C++ compiler (e.g., GCC, Clang, MSVC)
- A terminal that supports UTF-16 encoding (for displaying special characters)

## Compilation and Running


### Key Sections in the `README.md`:

1. **Project Overview**: Brief description of the game and its functionality.
2. **Key Features**: Summary of the game’s core features (e.g., Dijkstra's algorithm, hidden achievements, random grid generation).
3. **How to Play**: A clear, step-by-step explanation for users to start the game and understand the gameplay mechanics.
4. **Functions**: Brief descriptions of key functions in the code (such as `Grid`, `randomPt`, `dijkstra`, etc.).
5. **Requirements**: Any dependencies or tools required to run the game (e.g., C++11, compiler).
6. **Compilation and Running Instructions**: Step-by-step guide on how to compile and run the game.
7. **Example Output**: Sample output of the game when the user completes the path.
8. **Contributing**: Instructions for anyone who wants to contribute to the project.
9. **License**: Details of the licensing (typically MIT or other open-source licenses).
10. **Acknowledgements**: Credit for algorithms or resources used in the project.

This `README.md` provides a complete guide for users to get started with the game and for contributors to participate in the project.


1. Clone the repository:
   ```bash
   git clone https://github.com/lana855/pathfinding-game.git
   cd pathfinding-game
