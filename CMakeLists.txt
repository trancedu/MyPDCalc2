cmake_minimum_required(VERSION 3.15)

# Set the project name and version
project(MyPDCalc2 VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the backend library
add_library(backend SHARED
    backend/command.h
    backend/CommandEnteredObserver.h
    backend/CommandFactory.h
    backend/CommandInterpreter.h
    backend/CommandManager.h
    backend/DynamicLoader.h
    backend/plugin.h
    backend/PluginLoader.h
    backend/stack.h
    backend/stackChangedObserver.h
    backend/StackPluginInterface.h
    backend/WindowsDynamicLoader.h
    backend/stack.cpp
    backend/StackPluginInterface.cpp
)

# Add the utilities library
add_library(utilities SHARED
    utilities/exception.h
    utilities/observer.h
    utilities/publisher.h
    utilities/Tokenizer.h
    utilities/observer.cpp
    utilities/publisher.cpp
)

# Add the ui library
add_library(ui SHARED
    ui/CLI.h
    ui/UserInterface.h
    ui/cli_main.cpp
)

# Include directories for all libraries
target_include_directories(backend PUBLIC ${CMAKE_SOURCE_DIR}/backend ${CMAKE_SOURCE_DIR}/utilities)
target_include_directories(utilities PUBLIC ${CMAKE_SOURCE_DIR}/utilities)
target_include_directories(ui PUBLIC ${CMAKE_SOURCE_DIR}/ui ${CMAKE_SOURCE_DIR}/utilities ${CMAKE_SOURCE_DIR}/backend)

# Link the main executable with the libraries
add_executable(MyPDCalc2 MyPDCalc2/cli_main.cpp)
target_link_libraries(MyPDCalc2 PRIVATE backend utilities ui)

# Set the output directory for the libraries and executable
set_target_properties(backend utilities ui MyPDCalc2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Add any additional settings or dependencies as needed


# Command For CMake:
# mkdir build
# cd build
# cmake .. -DCMAKE_CXX_COMPILER=clang++

# make