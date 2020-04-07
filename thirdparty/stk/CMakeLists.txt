project(JustKeyboard)

include_directories(include)

add_library(STK STATIC src/Stk.cpp src/SineWave.cpp src/DelayL.cpp src/OnePole.cpp src/BiQuad.cpp src/ADSR.cpp src/Bowed.cpp)
