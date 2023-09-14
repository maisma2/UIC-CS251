cmake_minimum_required(VERSION 3.25)
project(CS251Proj2)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(CS251Proj2 main.cpp AutocompleteList.h)
target_link_libraries(CS251Proj2 gtest_main)
add_test(NAME CS251Proj2_test COMMAND CS251Proj2)
