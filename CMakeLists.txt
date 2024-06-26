cmake_minimum_required(VERSION 3.8)
project(NPG)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        src/savegame.cpp
        src/savegame.cpp
        src/ImGuiBase.h
        src/ImGuiBase.cpp
        src/editor/GameBase.h
        src/editor/GameBase.cpp
)

add_executable(NPG src/main.cpp
        ${SOURCE_FILES}
        src/stats.hpp
        src/stats.cpp
        src/frazy.h

)

add_executable(
        NPG__test
        ${SOURCE_FILES}
)

enable_testing()

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Stb REQUIRED)

target_link_libraries(NPG PRIVATE glad::glad)
target_link_libraries(NPG PRIVATE glfw)
target_link_libraries(NPG PRIVATE imgui::imgui)
target_include_directories(NPG PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(NPG__test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(NPG__test PRIVATE glad::glad)
target_link_libraries(NPG__test PRIVATE glfw)
target_link_libraries(NPG__test PRIVATE imgui::imgui)

file(COPY fonts/Roboto.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY fonts/Comic.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY fonts/Fjalla.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY fonts/Playwrite.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY fonts/Lora.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})