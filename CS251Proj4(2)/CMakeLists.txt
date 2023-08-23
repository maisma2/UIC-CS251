cmake_minimum_required(VERSION 3.12)
project(YourProjectName)  # Replace "YourProjectName" with your actual project name

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add the source files to your project
set(SOURCES
        hashmap.h
        hashmap.cpp
        main.cpp
        util.h
        )

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# If you want to include header files from the project's root directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
