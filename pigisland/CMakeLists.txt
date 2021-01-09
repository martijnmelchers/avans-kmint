 project(pigisland)

 # Author: Jeroen de Haas <jah.dehaas@avans.nl>
 cmake_minimum_required(VERSION 3.1.3)
 set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

 if (MSVC)
     add_compile_options(/W3)
 else ()
     add_compile_options(-Wall -Wpedantic)#  -Werror)
     add_compile_options("$<$<CONFIG:DEBUG>:-g>")
 endif ()


 add_executable(pigisland
                src/kmint/pigisland/main.cpp
                src/kmint/pigisland/node_algorithm.cpp
                src/kmint/pigisland/resources.cpp
                src/kmint/pigisland/shark.cpp
                src/kmint/pigisland/boat.cpp
                src/kmint/pigisland/pig.cpp
                
                # States
                src/kmint/pigisland/state/state.hpp
                src/kmint/pigisland/state/porcusvincit/wander_state.cpp
                src/kmint/pigisland/state/porcusvincit/wander_state.hpp
                src/kmint/pigisland/state/porcusvincit/grain_dock.cpp
                src/kmint/pigisland/state/porcusvincit/grain_dock.hpp
                src/kmint/pigisland/state/porcusvincit/grass_dock.cpp
                src/kmint/pigisland/state/porcusvincit/grass_dock.hpp
                src/kmint/pigisland/state/porcusvincit/tree_dock.cpp
                src/kmint/pigisland/state/porcusvincit/tree_dock.hpp
                
                # A*
                src/kmint/astar/astar.cpp
                src/kmint/astar/astar.hpp
                
                # Force Driven
                src/kmint/pigisland/force_driven/PhysicsActor.cpp
                src/kmint/pigisland/force_driven/PhysicsActor.hpp
                src/kmint/pigisland/force_driven/SteeringBehaviors.cpp
                src/kmint/pigisland/force_driven/SteeringBehaviors.hpp)

 target_compile_features(pigisland PUBLIC cxx_std_17)
 target_link_libraries(pigisland PRIVATE kmint)
 target_include_directories(pigisland PRIVATE
                            src
                            include)


 add_custom_command(TARGET pigisland POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
                    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")

 # Does not work for MinGW CMake
 #add_custom_target(pigisland-resources ALL
 #  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")