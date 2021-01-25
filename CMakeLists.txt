cmake_minimum_required(VERSION 3.10)
project(AgeOfWar)

set(CMAKE_CXX_STANDARD 17)


include_directories(SYSTEM ./libs)
#include_directories(SYSTEM ./libs/cereal/archives)

add_executable(AgeOfWar main.cpp src/units/IBaseUnit.hpp src/units/Fantassin.cpp src/units/Fantassin.hpp src/units/Archer.cpp src/units/Archer.hpp src/units/Catapult.cpp src/units/Catapult.hpp src/players/IPlayer.cpp src/players/IPlayer.hpp src/players/HumanPlayer.cpp src/players/HumanPlayer.hpp src/players/ComputerPlayer.cpp src/players/ComputerPlayer.hpp src/units/IAttackable.hpp src/units/IAttacking.hpp src/players/Base.cpp src/players/Base.hpp src/utility/IDrawable.hpp src/game/Board.cpp src/game/Board.hpp src/game/BuyingManager.cpp src/game/BuyingManager.hpp src/game/GameManager.cpp src/game/GameManager.hpp src/game/GameLogger.cpp src/game/GameLogger.hpp src/game/actions/IAction.hpp src/game/actions/ActionAttack.cpp src/game/actions/ActionAttack.hpp src/game/actions/ActionMove.cpp src/game/actions/ActionMove.hpp src/game/actions/ActionNone.cpp src/game/actions/ActionNone.hpp src/utility/Helper.hpp)