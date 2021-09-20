cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VESRION})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    factorial.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-fsanitize=address -fno-omit-frame-pointer"
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -pedantic -Werror -Wshadow
)