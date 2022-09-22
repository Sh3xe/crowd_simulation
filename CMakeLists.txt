cmake_minimum_required(VERSION 3.0)
project(simulation_foule LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED TRUE )

file( GLOB_RECURSE source_files "./source/*.cpp" "./source/*.hpp" )

add_executable( simulation_foule ${source_files} )

target_include_directories( simulation_foule PUBLIC "dependencies/include" )
target_link_directories( simulation_foule PUBLIC "dependencies/lib" )
target_link_libraries( simulation_foule sfml-graphics sfml-window sfml-system )