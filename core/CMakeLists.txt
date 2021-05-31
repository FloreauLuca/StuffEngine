#source files
file(GLOB_RECURSE ENGINE_SRC src/engine/*.cpp include/engine/*.h)
file(GLOB_RECURSE GRAPHICS_SRC src/graphics/*.cpp include/graphics/*.h)
file(GLOB_RECURSE UTILITY_SRC src/utility/*.cpp include/utility/*.h)

source_group("Graphics"				FILES ${GRAPHICS_SRC})
source_group("Engine"				FILES ${ENGINE_SRC})
source_group("Utility"				FILES ${UTILITY_SRC})

List(APPEND CORE_SRC
        ${ENGINE_SRC}
        ${GRAPHICS_SRC}
        ${UTILITY_SRC})

add_library(Core STATIC ${CORE_SRC})
target_include_directories(Core PUBLIC include/)
target_link_libraries(Core sfml-graphics)
