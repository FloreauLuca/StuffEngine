include_directories("include/")

file(GLOB_RECURSE art_visualization_src include/*.h src/*.cpp)

add_executable(art_visualization ${art_visualization_src})

target_link_libraries(art_visualization PUBLIC Core)
set_target_properties (art_visualization PROPERTIES FOLDER Main)