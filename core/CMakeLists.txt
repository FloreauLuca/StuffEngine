#source files
file(GLOB_RECURSE ENGINE_SRC src/engine/*.cpp include/engine/*.h)
file(GLOB_RECURSE GRAPHICS_SRC src/graphics/*.cpp include/graphics/*.h)
file(GLOB_RECURSE UTILITY_SRC src/utility/*.cpp include/utility/*.h)
file(GLOB_RECURSE MATH_SRC src/math/*.cpp include/math/*.h)

source_group("Graphics"				FILES ${GRAPHICS_SRC})
source_group("Engine"				FILES ${ENGINE_SRC})
source_group("Utility"				FILES ${UTILITY_SRC})
source_group("Math"				FILES ${MATH_SRC})

List(APPEND CORE_SRC
        ${ENGINE_SRC}
        ${GRAPHICS_SRC}
        ${UTILITY_SRC}
        ${MATH_SRC})

add_library(core STATIC ${CORE_SRC})
target_include_directories(core PUBLIC include/)
target_link_libraries(core tracy sfml-system sfml-window sfml-network sfml-graphics sfml-audio sfml-main)
