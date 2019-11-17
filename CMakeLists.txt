cmake_minimum_required(VERSION 3.14)
project(assignment3)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment3 Dice.cpp Dice.h Player.cpp Player.h Map.cpp Map.h Cards.h Cards.cpp GameEngine.cpp GameEngine.h GameEngine2.cpp GameEngine2.h ReinforcementDriver.cpp PlayerStrategies.h PlayerStrategies.cpp MapLoader.cpp MapLoader.h GameEngineDriver2.cpp GameObservers.cpp GameObservers.h)
