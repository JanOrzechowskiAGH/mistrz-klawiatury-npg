cmake_minimum_required(VERSION 3.8)
project(NPG)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        src/ImGuiBase.h
        src/ImGuiBase.cpp
        src/editor/EditorBase.h
        src/editor/EditorBase.cpp
        src/system/File.cpp
        src/system/File.h
        src/system/FileDialogManager.cpp
        src/system/FileDialogManager.h
)

add_executable(NPG src/main.cpp
        ${SOURCE_FILES}
        src/system/ImageLoader.cpp
        src/system/ImageLoader.h
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