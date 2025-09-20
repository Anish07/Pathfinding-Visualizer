# Pathfinding Visualizer (C++17)

A simple **console-based pathfinding visualizer** that demonstrates graph search algorithms on ASCII grid maps.  
It highlights **algorithm design, optimization, and systems-level programming** with C++17.

---

## Features
- Supports **A\***, **BFS**, and **DFS** algorithms  
- Reads an ASCII grid from stdin (`S` = start, `G` = goal, `#` = wall, `.` = open)  
- Outputs the shortest path marked with `*`  
- Demonstrates use of **priority queues, hash maps, and heuristic search**  
- Runs entirely in the console (no GUI dependencies)

---

## Build Instructions

### Prerequisites
- CMake (>= 3.16)
- C++17-compatible compiler (GCC, Clang, or MSVC)

### Steps
```bash
# Clone this repo
git clone https://github.com/Anish07/pathfinding-visualizer.git
cd pathfinding-visualizer

# Configure and build
cmake -S . -B build
cmake --build build -j

# Run
./build/pathfinding_visualizer
