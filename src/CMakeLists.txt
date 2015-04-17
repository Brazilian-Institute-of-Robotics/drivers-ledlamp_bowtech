rock_library(ledlamp_bowtech
    SOURCES BowtechDriver.cpp
    HEADERS BowtechDriver.hpp
    DEPS_PKGCONFIG iodrivers_base)

#rock_executable(ledlamp_bowtech_bin Main.cpp
#    DEPS ledlamp_bowtech)

