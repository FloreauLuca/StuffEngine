
file(GLOB_RECURSE noise_inc include/algo/noise/*.h)
file(GLOB_RECURSE noise_src src/noise/*.cpp)
file(GLOB_RECURSE sort_inc include/algo/sort/*.h)
file(GLOB_RECURSE sort_src src/sort/*.cpp)
file(GLOB_RECURSE path_inc include/algo/path/*.h)
file(GLOB_RECURSE path_src src/path/*.cpp)
file(GLOB_RECURSE search_inc include/algo/search/*.h)
file(GLOB_RECURSE search_src src/search/*.cpp)
file(GLOB_RECURSE steering_inc include/algo/steering/*.h)
file(GLOB_RECURSE steering_src src/steering/*.cpp)

source_group("Noise/Header"				FILES ${noise_inc})
source_group("Noise/Source"				FILES ${noise_src})
source_group("Sort/Header"				FILES ${sort_inc})
source_group("Sort/Source"				FILES ${sort_src})
source_group("Path/Header"				FILES ${path_inc})
source_group("Path/Source"				FILES ${path_src})
source_group("Search/Header"				FILES ${search_inc})
source_group("Search/Source"				FILES ${search_src})
source_group("Steering/Header"				FILES ${steering_inc})
source_group("Steering/Source"				FILES ${steering_src})

List(APPEND algo_lib_src
        ${noise_inc}
        ${noise_src}
        ${sort_inc}
		${sort_src}
        ${path_inc}
		${path_src}
        ${search_inc}
		${search_src}
        ${steering_inc}
		${steering_src})
		
add_library(algo_lib STATIC ${algo_lib_src})
target_link_libraries(algo_lib PUBLIC core)
target_include_directories(algo_lib PUBLIC "include/")
set_target_properties (algo_lib PROPERTIES FOLDER Common)

