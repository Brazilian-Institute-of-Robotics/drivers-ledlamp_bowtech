rock_library(ledlamp_bowtech
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(ledlamp_bowtech_bin Main.cpp
    DEPS ledlamp_bowtech)

