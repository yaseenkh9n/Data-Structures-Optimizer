

cmake_minimum_required(VERSION 3.16)
project(DataStructureOptimizer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

# Set UIC output directory
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/gui)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/analyzer
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
)

# Source files
set(SOURCES
    main.cpp
    gui/mainwindow.cpp
    gui/newAnalysis.cpp
    gui/results.cpp
    analyzer/DataAnalyzer.cpp
    analyzer/RecommendationEngine.cpp
    benchmark/Benchmark.cpp
    benchmark/PerformanceMetrics.cpp
)

# Header files
set(HEADERS
    gui/mainwindow.h
    gui/newAnalysis.h
    gui/results.h
    analyzer/DataAnalyzer.h
    analyzer/RecommendationEngine.h
    benchmark/Benchmark.h
    benchmark/PerformanceMetrics.h
    core/BST.h
    core/HashMap.h
    core/Heap.h
    core/Trie.h
    core/Queue.h
    core/Graph.h
)

# UI files
set(UI_FILES
    gui/mainwindow.ui
    gui/newAnalysis.ui
    gui/results.ui
)

# Resource files
set(RESOURCES
    resources/resources.qrc
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
