file(GLOB_RECURSE kernel_lib_src include/*.h src/*.cpp)

find_package(OpenCL REQUIRED)
add_library(kernel_lib STATIC ${kernel_lib_src})
target_link_libraries(kernel_lib PUBLIC core OpenCL::OpenCL)
target_include_directories(kernel_lib PUBLIC "include/")
set_target_properties (kernel_lib PROPERTIES FOLDER Common)

