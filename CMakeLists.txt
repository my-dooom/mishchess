cmake_minimum_required(VERSION 3.16)
project(mishchess C)

set(CMAKE_C_STANDARD 99)

# include(FetchContent)
# FetchContent_Declare(
#   raylib
#   GIT_REPOSITORY https://github.com/raysan5/raylib.git
#   GIT_TAG 5.5
# )

file(GLOB_RECURSE SOURCES src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/raylib/src ${CMAKE_SOURCE_DIR}/src/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/raylib/build/raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib winmm gdi32 opengl32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets to build directory"
)
# FetchContent_MakeAvailable(raylib)
# target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
# if(WIN32)
#     target_link_options(${PROJECT_NAME} PROPERITES WIN32_EXECUTABLE TRUE)
# endif()
