project(JustKeyboard)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

#add_subdirectory(Audio)


add_executable(JustKeyboard main.cpp UI/MainWindow.cpp UI/KeyboardWidget.cpp UI/KeyboardWidget.h Note.h Audio/QRTAudioIO.cpp Audio/QRTAudioIO.h Audio/AudioManager.cpp Audio/AudioManager.h Audio/StringAudioGen.cpp Audio/StringAudioGen.h Ratios.h)
target_link_libraries(JustKeyboard PUBLIC Qt5::Widgets Qt5::Multimedia STK)