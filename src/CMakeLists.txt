project(JustKeyboard)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(Audio)

add_executable(JustKeyboard main.cpp UI/MainWindow.cpp UI/KeyboardWidget.cpp UI/KeyboardWidget.h Note.h)
target_link_libraries(JustKeyboard PUBLIC Qt5::Widgets JKPlayback)