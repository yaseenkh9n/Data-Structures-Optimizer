# Data Structure Optimizer

A Qt-based desktop application that analyzes dataset characteristics and recommends optimal data structures for improved performance.

## Features

- **Intelligent Analysis**: Analyzes operation patterns, data types, and access frequencies
- **Performance Benchmarking**: Real-time performance comparison across multiple data structures
- **Visual Insights**: Interactive charts displaying time and space complexity metrics
- **Smart Recommendations**: AI-driven suggestions based on workload characteristics
- **Data Structures**: HashMap, BST, Heap, Trie, Queue, Graph

## Requirements

- **Qt6** (Core, Gui, Widgets, Charts)
- **CMake** 3.16+
- **C++17** compiler (GCC/Clang/MSVC)

## Build & Run

```bash
cd build
cmake ..
make
./DataStructureOptimizer
```

## Project Structure

```
├── core/          # Data structure implementations
├── analyzer/      # Recommendation engine
├── benchmark/     # Performance testing framework
├── gui/           # Qt interface components
└── resources/     # UI assets and icons
```

## Usage

1. **New Analysis**: Configure dataset parameters and operation patterns
2. **Run Benchmark**: Execute performance tests across data structures
3. **View Results**: Analyze recommendations and performance metrics
4. **Load/Save**: Persist analysis configurations for reuse

## Author

- **Yaseen Khan**
- **Rana Abdullah**
- **Anas Mehboob**  
Data Structures - Semester Project

## License

Academic Project
