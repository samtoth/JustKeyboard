project(JustKeyboard)

find_library(stk REQUIRED)

add_library(JKPlayback STATIC Playback.cpp)
target_link_libraries(JKPlayback PUBLIC stk -lpthread -lasound)