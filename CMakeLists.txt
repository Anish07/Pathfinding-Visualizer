
project(pathfinding_visualizer LANGUAGES CXX)
add_executable(pathfinding_visualizer src/main.cpp)
target_compile_features(pathfinding_visualizer PRIVATE cxx_std_17)
