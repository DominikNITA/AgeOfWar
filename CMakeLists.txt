cmake_minimum_required(VERSION 3.15)
project(AgeOfWar)

set(CMAKE_CXX_STANDARD 17)

add_executable(AgeOfWar main.cpp src/units/IUnit.cpp src/units/IUnit.hpp src/units/Fantassin.cpp src/units/Fantassin.hpp src/units/Archer.cpp src/units/Archer.hpp src/units/Catapult.cpp src/units/Catapult.hpp src/units/SuperSoldier.cpp src/units/SuperSoldier.hpp src/players/IPlayer.cpp src/players/IPlayer.hpp src/players/HumanPlayer.cpp src/players/HumanPlayer.hpp src/players/ComputerPlayer.cpp src/players/ComputerPlayer.hpp src/units/IAttackable.cpp src/units/IAttackable.hpp)