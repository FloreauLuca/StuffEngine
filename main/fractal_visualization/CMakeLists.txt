include_directories("include/")

file(GLOB_RECURSE fractal_visualization_src include/*.h src/*.cpp ${DATA_DIR}/*.cl)

add_executable(fractal_visualization ${fractal_visualization_src})

target_link_libraries(fractal_visualization PUBLIC core kernel_lib)
set_target_properties (fractal_visualization PROPERTIES FOLDER Main)