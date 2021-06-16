
file(GLOB_RECURSE noise_inc include/algo/noise/*.h)
file(GLOB_RECURSE noise_src src/noise/*.cpp)
file(GLOB_RECURSE sort_inc include/algo/sort/*.h)
file(GLOB_RECURSE sort_src src/sort/*.cpp)

source_group("Noise/Header"				FILES ${noise_inc})
source_group("Noise/Source"				FILES ${noise_src})
source_group("Algo/Header"				FILES ${sort_inc})
source_group("Algo/Source"				FILES ${sort_src})

List(APPEND algo_lib_src
        ${noise_inc}
        ${noise_src}
        ${sort_inc}
		${sort_src})
		
add_library(algo_lib STATIC ${algo_lib_src})
target_link_libraries(algo_lib PUBLIC core)
target_include_directories(algo_lib PUBLIC "include/")
set_target_properties (algo_lib PROPERTIES FOLDER Common)

